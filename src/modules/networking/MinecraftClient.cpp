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
        for (int i = 0; i < newBytes.size(); i++)
        {
            hexBytes += std::format("%1$2x", newBytes[i]);
        }
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
    uint remaining = currentPacketLength -
        packetAccumulator.size();
    size_t newSize = packetAccumulator.size() +
        newData.size();
    if (packetAccumulator.size() > currentPacketLength)
    {
        Logger::warn("I accumulated more data than I should have. "
                     "Currently there is no automatic \"repair\" "
                     "as this is a very early version of this library. "
                     "This should never happen anyways. This socket will break. "
                     "Behavior is undefined.");
        return;
    }
    if (currentPacketLength == 0)
    {
        uint bytesConsumed;

        currentPacketLength = VarIntCodec::CODEC.deserialize(newData, bytesConsumed);

        if (newData.size() - bytesConsumed > remaining)
        {
            // TODO: Merge into one function
            packetAccumulator.insert(
          packetAccumulator.end(),
               newData.begin(),
               newData.begin() + remaining
            );
            std::vector<unsigned char> bytesNotConsumed;

            bytesNotConsumed.insert(
                bytesNotConsumed.end(),
                newData.begin() + bytesConsumed,
                newData.begin() + bytesConsumed + remaining
            );
            currentPacketLength = 0;
            accumulateOrReceive(bytesNotConsumed);
        }
        packetAccumulator.insert(
            packetAccumulator.end(),
            newData.begin() + bytesConsumed,
            newData.end()
        );
        return;
    }
    if (packetAccumulator.size() < currentPacketLength)
    {
        if (newData.size() < remaining)
        {
            packetAccumulator.insert(
                packetAccumulator.end(),
                newData.begin(),
                newData.end()
            );
            return;
        }
        // TODO: Merge into one function
        packetAccumulator.insert(
            packetAccumulator.end(),
            newData.begin(),
            newData.begin() + remaining
        );
        std::vector<unsigned char> bytesNotConsumed;

        bytesNotConsumed.insert(
            bytesNotConsumed.end(),
            newData.begin() + remaining,
            newData.end()
        );
        currentPacketLength = 0;
        accumulateOrReceive(bytesNotConsumed);

        return;
    }
    if (newSize >= currentPacketLength)
    {
        std::copy(
            newData.begin(),
            newData.end() - (newSize - currentPacketLength),
            packetAccumulator.end()
        );
        currentPacketLength = 0;

        packetDataFunction(std::move(packetAccumulator),
            *this);
        packetAccumulator = {};
    }
}

// PUBLIC
void MinecraftClient::write(std::vector<unsigned char> bytes, size_t size)
{
    async_write(getSocket(), buffer(bytes),
        std::bind(&MinecraftClient::handleWrite, shared_from_this(),
            placeholders::error,
            placeholders::bytes_transferred));
}