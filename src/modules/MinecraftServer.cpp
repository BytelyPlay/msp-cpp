module;
#include <boost/asio.hpp>

module MinecraftServer;

// PUBLIC
MinecraftServer::MinecraftServer(io_context& io, string listenIp, uint16 port) :
io(io), acceptor(io, tcp::endpoint(
    make_address(listenIp),
    port
    ))
{
}
// PRIVATE
