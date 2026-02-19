module;
#include <string>
#include <thread>
#include <boost/asio.hpp>
#include <latch>

export module MinecraftProtocol;

#include "BoostNamespaces.hpp"
#include "Types.hpp"

export class MinecraftProtocol
{
public:
    MinecraftProtocol(uint8 threadCount);

    void init();
    void shutdown();

    // This blocks until the server has shutdown.
    void awaitShutdown();
public:
    io_context& getIo();
private:
    // Annoyingly long return type
    executor_work_guard<io_context::basic_executor_type<std::allocator<void>, 0>> getWorkGuard() const;

    void setupThreads();
private:
    const uint8 threadCount;
    std::unique_ptr<io_context> io;

    std::vector<std::thread> threads;
    std::latch shutdownLatch = std::latch(1);
public:
    MinecraftProtocol operator=(const MinecraftProtocol&) = delete;
    MinecraftProtocol(const MinecraftProtocol&) = delete;
};