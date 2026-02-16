module;
#include <iostream>
#include <boost/asio.hpp>

module MinecraftProtocol;
import Logger;

// PUBLIC
MinecraftProtocol::MinecraftProtocol(string ip, uint16 port, uint8 threadCount) :
  ip(ip), port(port), threadCount(threadCount)
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

// PRIVATE
executor_work_guard<basic_system_executor<execution::detail::blocking::possibly_t<>,
execution::detail::relationship::
fork_t<>, std::allocator<void>>>
MinecraftProtocol::getWorkGuard() const
{
    static auto workGuard = make_work_guard(io);
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
    }
}
