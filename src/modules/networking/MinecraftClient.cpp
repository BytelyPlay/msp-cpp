module;
#include <memory>
#include <boost/asio.hpp>

module MinecraftClient;
import MinecraftProtocol;
import Logger;
import VarIntCodec;
import TypedInputStream;
import MinecraftServer;
import Packets;
import CodecParsingException;

// PUBLIC
std::shared_ptr<MinecraftClient> MinecraftClient::create(
        MinecraftProtocol& protocol,
        std::function<void(std::vector<unsigned char>,
        MinecraftClient&)> packetReceivedFunc
)
{
    return
    std::shared_ptr<MinecraftClient>(new MinecraftClient(protocol, packetReceivedFunc));
}
// PUBLIC
void MinecraftClient::init()
{
    initRead();
}
// PRIVATE
void MinecraftClient::initRead()
{
    getSocket().async_read_some(
    buffer(readBuffer),
    std::bind(&MinecraftClient::handleRead, this,
        placeholders::error, placeholders::bytes_transferred)
    );
}

// PUBLIC
void MinecraftClient::disconnect()
{
    if (disconnected)
    {
        Logger::warn("Tried to disconnect twice.");
    }

    error_code error;
    getSocket().shutdown(
        socket_base::shutdown_both,
        error);
    getSocket().close(error);

    if (error)
        Logger::warn("Error occurred during shutdown: " + error.what());
    disconnected = true;
}

// PUBLIC
tcp::socket& MinecraftClient::getSocket()
{
    return socket;
}

// PRIVATE
MinecraftClient::MinecraftClient(MinecraftProtocol& protocol,
    std::function<void(std::vector<unsigned char>,
        MinecraftClient&)> packetReceivedFunc) :
socket(tcp::socket(protocol.getIo())),
protocol(protocol), packetDataFunction(packetReceivedFunc)
{
}

void MinecraftClient::handleWrite(
    error_code ec, size_t bytesTransferred
    )
{
    if (ec)
    {
        Logger::warn("Couldn't write to tcp socket: " + ec.what());
    }
}

void MinecraftClient::handleRead(const error_code ec, size_t bytesTransferred)
{
    if (!ec)
    {
        std::vector<unsigned char> newBytes;

        newBytes.insert(
            newBytes.end(),
            readBuffer.begin(),
            readBuffer.begin() + bytesTransferred
        );
        std::string hexBytes;
        for (unsigned char& newByte : newBytes)
        {
            hexBytes += std::format("%1$2x", newByte);
        }
        Logger::debug(hexBytes);
        accumulateOrReceive(
            std::move(newBytes)
        );
    } else if (ec == error::eof)
    {
        disconnected = true;
        getSocket().shutdown(socket_base::shutdown_both);
        getSocket().close();

        return;
    } else
    {
        Logger::warn("Error occurred while reading data: " + ec.what());
    }
    initRead();
}
// PRIVATE
// TODO: Make more methods instead of one giant method. And also completely rewrite this.
void MinecraftClient::accumulateOrReceive(std::vector<unsigned char> newData)
{
    uint newSize = newData.size() + packetAccumulator.size();

    if (currentPacketLength <= 0)
    {
        // New Packet
        createNewPacket(newData);
    } else if (packetAccumulator.size() > currentPacketLength)
    {
        // Something went wrong
        // We collected too much data.
        Logger::warn("Accidentally accumulated too much data for the packet, "
                     "there is no recovery. "
                     "This means the client this happened on is broken.");
    } else if (newSize >= currentPacketLength)
    {
        // Packet collected, and there is also a second one.
        size_t amountOfBytesLeft = currentPacketLength - packetAccumulator.size();

        packetAccumulator.insert(
            packetAccumulator.end(),
            newData.begin(),
            newData.begin() + amountOfBytesLeft
        );
        packetDataFunction(std::move(packetAccumulator), *this);
        packetAccumulator = {};

        currentPacketLength = 0;
        Logger::debug("REMOVE: " + std::to_string(amountOfBytesLeft));

        if (newData.size() - amountOfBytesLeft > 0)
            createNewPacket(
                removeFirstBytes(
                    amountOfBytesLeft,
                    newData
                )
            );
    } else
    {
        // std::copy is quite optimized for this. We use it for that reason.
        packetAccumulator.insert(
            packetAccumulator.end(),
            newData.begin(),
            newData.end()
        );
    }
}

void MinecraftClient::createNewPacket(std::vector<unsigned char> newData)
{
    try {
        uint bytesConsumedByVarInt;

        // TODO: Handle edge case: not the whole packet length was sent.
        currentPacketLength =
            VarIntCodec::CODEC.deserialize(newData, bytesConsumedByVarInt);

        if (currentPacketLength <= 0)
        {
            Logger::warn("Packet Length is less than or equals 0... Something is wrong, "
                         "the packet length is " +
                std::to_string(currentPacketLength));
            // return;
        }

        if (newData.size() - bytesConsumedByVarInt < currentPacketLength)
        {
            packetAccumulator.insert(
            packetAccumulator.end(),
                newData.begin() + bytesConsumedByVarInt,
                newData.end()
            );
        } else if (newData.size() - bytesConsumedByVarInt >= currentPacketLength) {
            accumulateOrReceive(
                removeFirstBytes(bytesConsumedByVarInt, newData)
            );
        }
    } catch (CodecParsingException& e)
    {
        Logger::warn(std::string("Couldn't parse Packet Length, "
                     "I do not handle the possible edge case where "
                     "the packet length isn't fully sent, "
                     "this may be what is happening. e.what(): ") + e.what());
    }
}

std::vector<unsigned char> MinecraftClient::removeFirstBytes(size_t amount,
    std::vector<unsigned char> data)
{
    return { data.begin() + amount,
        data.end() };
}

// PUBLIC
void MinecraftClient::write(std::vector<unsigned char> bytes, size_t size)
{
    async_write(getSocket(), buffer(bytes),
        std::bind(&MinecraftClient::handleWrite, shared_from_this(),
            placeholders::error,
            placeholders::bytes_transferred));
}