module;
#include <string>
#include <thread>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/address.hpp>

export module MinecraftProtocol;

using string = std::string;

using uint = unsigned int;

using uint8 = unsigned char;
using uint16 = unsigned short;
using uint32 = unsigned int;
using uint64 = unsigned long;

using namespace boost::asio;
using namespace ip;
using namespace boost::system;

export class MinecraftProtocol
{
public:
    MinecraftProtocol(string ip, uint16 port, uint8 threadCount);
    void init();
private:
    executor_work_guard<basic_system_executor<execution::detail::blocking::possibly_t<>, execution::detail::relationship
    ::
    fork_t<>, std::allocator<void>>> getWorkGuard() const;

    void setupThreads();
private:
    const string ip;
    const uint16 port;

    const uint8 threadCount;
    std::unique_ptr<io_context> io;

    std::vector<std::thread> threads;
};