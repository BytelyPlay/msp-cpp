module;
#include <boost/asio.hpp>
#include <boost/asio.hpp>
#include <boost/asio.hpp>

module MinecraftServer;
import MinecraftProtocol;
import MinecraftClient;
import Logger;

// PUBLIC
MinecraftServer::MinecraftServer(string listenIp,
    uint16 port, MinecraftProtocol& protocol) :
io(protocol.getIo()), protocol(protocol), acceptor(io, tcp::endpoint(
    make_address(listenIp),
    port
    ))
{
    startAccept();
}
// PUBLIC
void MinecraftServer::shutdown()
{
    acceptor.close();
    shutdownLatch.count_down();
}

void MinecraftServer::awaitShutdown()
{
    shutdownLatch.wait();
}

// PRIVATE
void MinecraftServer::startAccept()
{
    auto client =
        MinecraftClient::create(protocol);

    acceptor.async_accept(
        client->getSocket(),
        std::bind(&MinecraftServer::handleAccept, this,
            client, placeholders::error)
        );
}

void MinecraftServer::handleAccept(std::shared_ptr<MinecraftClient> client, error_code ec)
{
    if (!ec)
    {
        string s = std::string("Daytime Server Offline");

        std::vector<unsigned char> sVector;
        sVector.append_range(s);

        client->init();
        client->write(std::move(sVector), s.size());
    } else
    {
        Logger::warn("Error in handling accept: " + ec.message());
    }
    startAccept();
}
