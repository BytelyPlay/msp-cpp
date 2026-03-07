module;
#include <memory>
#include <boost/asio.hpp>

module MinecraftClient;
import MinecraftProtocol;
import Logger;
import VarIntCodec;
import TypedInputStream;
import Packets;
import MinecraftServer;

// PUBLIC
std::shared_ptr<MinecraftClient> MinecraftClient::create(MinecraftProtocol& protocol)
{
    return
    std::shared_ptr<MinecraftClient>(new MinecraftClient(protocol));
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
MinecraftClient::MinecraftClient(MinecraftProtocol& protocol) :
socket(tcp::socket(protocol.getIo())),
protocol(protocol)
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
        std::vector<unsigned char> bytes;

        bytes.insert(
            bytes.end(),
            readBuffer.begin(),
            readBuffer.begin() + bytesTransferred
        );

        if (packetAccumulator.empty())
        {
            // This is a new Packet.
            uint varIntLength;
            currentPacketLength = VarIntCodec::CODEC
            .deserialize(bytes,
            varIntLength
            );

            if (bytes.size() - varIntLength >= currentPacketLength)
            {
                Packets
            }

            packetAccumulator.insert(
                packetAccumulator.end(),
                bytes.begin() + varIntLength,
                bytes.end()
            );
        } else
        {
        }
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
void MinecraftClient::accumulateOrReceive(std::vector<unsigned char>&& newData)
{
    if (packetAccumulator.size() > currentPacketLength)
    {
        Logger::warn("I accumulated more data than I should have. "
                     "Currently there is no automatic fix as this is a very early version of this library. "
                     "This should never happen anyways. This socket will break.");
        return;
    }
    size_t newSize = packetAccumulator.size() +
        newData.size();
    if (newSize >= currentPacketLength)
    {
        std::copy(
            newData.begin(),
            newData.end() - (newSize - currentPacketLength),
            packetAccumulator.end()
        );
        currentPacketLength = 0;

        Packets
        ::PacketsRegister
        ::getInstance()
        .receivedPacket(packetAccumulator, *server, protocol);
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