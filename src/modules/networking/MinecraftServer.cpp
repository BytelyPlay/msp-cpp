module;
#include <boost/asio.hpp>
#include <boost/asio.hpp>
#include <boost/asio.hpp>
#include <utility>

module MinecraftServer;
import MinecraftProtocol;
import MinecraftClient;
import Logger;
import Packets;

// PUBLIC
MinecraftServer::MinecraftServer(std::string listenIp,
    uint16_t port, MinecraftProtocol& protocol) :
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
        MinecraftClient::create(protocol,
            // not really worth making a whole new function for
            // It is really just a small call.
            [this](std::vector<unsigned char> vec, MinecraftClient& client)
            {
                Packets::PacketsRegister::getInstance()
                .receivedPacket(std::move(vec),
                    *this,
                    protocol,
                    client);
            });

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
        clients.push_back(client);

        std::string s = std::string("Daytime Server Offline");

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
