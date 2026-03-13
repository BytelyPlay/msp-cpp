module;
#include <string>
#include <boost/asio.hpp>
#include <latch>
#include <cstdint>
#include <string>

export module MinecraftServer;
import MinecraftProtocol;
import MinecraftClient;

#include "BoostNamespaces.hpp"

export class MinecraftServer
{
public:
    MinecraftServer(std::string listenIp, uint16_t port,
        MinecraftProtocol& protocol);
public:
    void shutdown();
    // This blocks until the server has shutdown.
    void awaitShutdown();
private:
    void startAccept();
    void handleAccept(std::shared_ptr<MinecraftClient>, error_code);
private:
    void packetDataListener(
        std::vector<unsigned char> vec,
        MinecraftClient& client
    );
    void clientShutdownListener(
        MinecraftClient& client
    );
private:
    io_context& io;
    tcp::acceptor acceptor;

    MinecraftProtocol& protocol;
    std::vector<std::shared_ptr<MinecraftClient>> clients;

    std::latch shutdownLatch = std::latch(1);
};