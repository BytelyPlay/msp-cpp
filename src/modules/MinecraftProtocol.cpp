module;
#include <iostream>
#include <boost/asio.hpp>

module MinecraftProtocol;

using namespace boost::asio;
// PUBLIC
MinecraftProtocol::MinecraftProtocol(string ip, uint16 port) :
  ip(ip), port(port)
{
}

void MinecraftProtocol::init()
{
    io_context io;
    ip::tcp::resolver resolver(io);
    ip::tcp::resolver::results_type endpoints =
        resolver.resolve(ip, "daytime");
    ip::tcp::socket socket(io);

    connect(socket, endpoints);

    std::vector<char> data(32);

    for (;;)
    {
        boost::system::error_code error;

        size_t size = socket.read_some(buffer(data), error);

        if (!data.empty())
        {
            std::cout << string(data.data());
        }

        if (error == error::eof)
            break;
        else if (error)
        {
            std::cout << "Error Occurred " + error.message();
        }
    }
}

// PRIVATE
