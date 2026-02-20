module;
#include <string>
#include <boost/asio.hpp>
#include <latch>

export module MinecraftServer;
import MinecraftProtocol;
import MinecraftClient;

#include "BoostNamespaces.hpp"
#include "Types.hpp"

export class MinecraftServer
{
public:
    MinecraftServer(string listenIp, uint16 port,
        MinecraftProtocol& protocol);
public:
    void shutdown();
    // This blocks until the server has shutdown.
    void awaitShutdown();
private:
    void startAccept();
    void handleAccept(std::shared_ptr<MinecraftClient>, error_code);
private:
    io_context& io;
    tcp::acceptor acceptor;

    MinecraftProtocol& protocol;
    std::vector<std::shared_ptr<MinecraftClient>> clients;

    std::latch shutdownLatch = std::latch(1);
};