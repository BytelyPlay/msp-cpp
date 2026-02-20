module;
#include <memory>
#include <boost/asio.hpp>

module MinecraftClient;
import MinecraftProtocol;
import Logger;

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
        unsigned char bytes[bytesTransferred];
        memcpy(bytes, readBuffer.data(), bytesTransferred);

        std::string s;
        for (int i = 0; i < bytesTransferred; i++)
        {
            s += std::format("0x{:02x} ", bytes[i]);
        }
        Logger::debug(s);
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

// Temporarily public
void MinecraftClient::write(std::vector<unsigned char> bytes, size_t size)
{
    async_write(getSocket(), buffer(bytes),
        std::bind(&MinecraftClient::handleWrite, shared_from_this(),
            placeholders::error,
            placeholders::bytes_transferred));
}