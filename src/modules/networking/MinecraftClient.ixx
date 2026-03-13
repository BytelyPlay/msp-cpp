module;
#include <memory>
#include <boost/asio.hpp>
#include <cstdint>

export module MinecraftClient;
import MinecraftProtocol;

#include "BoostNamespaces.hpp"

export class MinecraftClient : public std::enable_shared_from_this<MinecraftClient>
{
public:
    static std::shared_ptr<MinecraftClient> create(
        MinecraftProtocol& protocol,
        std::function<void(std::vector<unsigned char>,
        MinecraftClient&)> packetReceivedListener,
        std::function<void(MinecraftClient&)> shutdownListener
    );
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

    size_t currentPacketLength = 0;

    std::vector<unsigned char> readBuffer =
        std::vector<unsigned char>(1024);
    std::vector<unsigned char> packetAccumulator =
        std::vector<unsigned char>();

    MinecraftProtocol& protocol;

    // These std::functions are dirty, dirty workarounds.
    /* TODO: Please figure out something less dirty, the idea is that
    we need the MinecraftServer object to do stuff,
    but we can't make a field with it without importing it and
    forward declarations for some reason don't work. */
    std::function<void(std::vector<unsigned char>,
        MinecraftClient&)> packetDataListener;
    std::function<void(MinecraftClient&)> clientShutdownListener;
public:
    tcp::socket& getSocket();
private:
    MinecraftClient(
        MinecraftProtocol& protocol,
        std::function<void(std::vector<unsigned char>,
        MinecraftClient&)> packetReceivedListener,
        std::function<void(MinecraftClient&)> shutdownListener
    );

    void handleWrite(error_code ec, size_t bytesTransferred);
    void handleRead(error_code ec, size_t bytesTransferred);
private:
    /**
     * Either accumulates data in the vector or calls Packets#receivedPacket
     * @param newData The data to be accumulated or used.
     */
    void accumulateOrReceive(std::vector<unsigned char> newData);
    bool createNewPacket(std::vector<unsigned char> newData);

    std::vector<unsigned char> removeFirstBytes(size_t amount,
        std::vector<unsigned char> data);
public:
    // temporarily public until the packet system is created.
    void write(std::vector<unsigned char> bytes, size_t size);
public:
    MinecraftClient(const MinecraftClient&) = delete;
    MinecraftClient operator=(const MinecraftClient&) = delete;
};
