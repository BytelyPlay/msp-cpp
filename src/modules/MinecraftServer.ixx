module;
#include <string>
#include <boost/asio.hpp>

export module MinecraftServer;

using string = std::string;

using uint = unsigned int;

using uint8 = unsigned char;
using uint16 = unsigned short;
using uint32 = unsigned int;
using uint64 = unsigned long;

using namespace boost::asio;
using namespace ip;
using namespace boost::system;

export class MinecraftServer
{
public:
    MinecraftServer(io_context& io, string listenIp, uint16 port);
private:
    io_context& io;
    tcp::acceptor acceptor;
};