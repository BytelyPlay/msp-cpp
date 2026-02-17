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
    // TODO: handle reads
}

void MinecraftClient::disconnect()
{
    getSocket().close();
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

void MinecraftClient::handleRead()
{

}

// Temporarily public
void MinecraftClient::write(std::vector<unsigned char> bytes, size_t size)
{
    async_write(getSocket(), buffer(bytes),
        std::bind(&MinecraftClient::handleWrite, shared_from_this(),
            placeholders::error,
            placeholders::bytes_transferred));
}