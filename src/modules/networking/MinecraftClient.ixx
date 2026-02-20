module;
#include <memory>
#include <boost/asio.hpp>

export module MinecraftClient;
import MinecraftProtocol;
#include "BoostNamespaces.hpp"
#include "Types.hpp"

export class MinecraftClient : public std::enable_shared_from_this<MinecraftClient>
{
public:
    static std::shared_ptr<MinecraftClient> create(MinecraftProtocol& protocol);
public:
    void init();
private:
    void initRead();
public:
    void disconnect();
private:
    bool initialized = false;
    bool disconnected = false;
    tcp::socket socket;

    std::vector<unsigned char> readBuffer =
        std::vector<unsigned char>(1024);

    MinecraftProtocol& protocol;
public:
    tcp::socket& getSocket();
private:
    MinecraftClient(MinecraftProtocol& protocol);

    void handleWrite(error_code ec, size_t bytesTransferred);
    void handleRead(error_code ec, size_t bytesTransferred);
public:
    // temporarily public until the packet system is created.
    void write(std::vector<unsigned char> bytes, size_t size);
};
