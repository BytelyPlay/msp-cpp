module;
#include <memory>
#include <boost/asio.hpp>

export module MinecraftClient;
using string = std::string;

using uint = unsigned int;

using uint8 = unsigned char;
using uint16 = unsigned short;
using uint32 = unsigned int;
using uint64 = unsigned long;

using namespace boost::asio;
using namespace ip;
using namespace boost::system;

class MinecraftClient : public std::enable_shared_from_this<MinecraftClient>
{
public:
    static std::shared_ptr<MinecraftClient> create(tcp::socket& socket);
private:
    bool initialized = false;
    tcp::socket& socket;
private:
    // Socket should be a valid socket with a valid connection.
    MinecraftClient(tcp::socket& socket);
    void write(char* bytes, size_t amount);
};
