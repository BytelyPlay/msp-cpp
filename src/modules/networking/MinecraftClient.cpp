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

        std::copy_n(
            readBuffer.data(),
            readBuffer.size(),
            newBytes.end()
        );
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
void MinecraftClient::accumulateOrReceive(std::vector<unsigned char> newData)
{
    if (packetAccumulator.size() > currentPacketLength)
    {
        Logger::warn("I accumulated more data than I should have. "
                     "Currently there is no automatic \"repair\" "
                     "as this is a very early version of this library. "
                     "This should never happen anyways. This socket will break. "
                     "Behavior is undefined.");
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