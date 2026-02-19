module;
#include <boost/asio.hpp>

module MinecraftProtocol;
import Logger;

// PUBLIC
MinecraftProtocol::MinecraftProtocol(const uint8 threadCount) :
  threadCount(threadCount)
{
}

void MinecraftProtocol::init()
{
    try
    {
        io = std::make_unique<io_context>(threadCount);
        // The getting initializes the work guard
        getWorkGuard();
        setupThreads();
    } catch (std::exception& e)
    {
        Logger::error("Couldn't init Minecraft protocol: " +
            std::string(e.what()));
    }
}

void MinecraftProtocol::shutdown()
{
    getWorkGuard().reset();
    for (auto& t : threads)
        t.join();
    shutdownLatch.count_down();
}

void MinecraftProtocol::awaitShutdown()
{
    shutdownLatch.wait();
}

// PUBLIC
io_context& MinecraftProtocol::getIo()
{
    return *io;
}

// PRIVATE
executor_work_guard<io_context::basic_executor_type<std::allocator<void>, 0>>
MinecraftProtocol::getWorkGuard() const
{
    static auto workGuard = make_work_guard(io->get_executor());
    return workGuard;
}

void MinecraftProtocol::setupThreads()
{
    for (int i = 0; i < threadCount; i++)
    {
        std::thread t([this]()
        {
            io->run();
        });
        t.detach();
        threads.push_back(std::move(t));
    }
}
