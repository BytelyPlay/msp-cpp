module;
#include <memory>
#include <memory>
#include <string>
#include <vector>

export module Packets;
import PacketType;
import MinecraftServer;
import MinecraftProtocol;
import MinecraftClient;

#define DEFINE_PACKET(variableName, type) \
    const auto variableName = Packets::PacketsRegister::registerPacket(type);

// TODO: Read from a reports/packets.json and use the identifier to get the protocol ID.
export namespace Packets
{
    namespace S2C
    {

    }
    namespace C2S
    {
    }

    class PacketsRegister
    {
    public:
        static PacketsRegister& getInstance();
    public:
        /**
        * Handles a Packet being received.
        * @param data The Data excluding the Packet Length, but including the packet ID.
        * @param server
        * @param protocol
        */
        void receivedPacket(std::vector<unsigned char> data,
                            MinecraftServer& server,
                            MinecraftProtocol& protocol,
                            MinecraftClient& client);
    private:
        /**
        * Registers a packet.
        * @tparam T Has to be a PacketType subclass.
        * @param id Protocol Packet ID (will be replaced with the reports/packets.json thing)
        * @param identifier The stable Identifier (e.g. minecraft:example_packet)
        * @param type The Packet Type
        */
        // Performance wise, this may be very bad.
        // Perhaps we shouldn't move twice.
        template<typename T>
        T registerPacket(T type);
    private:
        PacketsRegister();
    private:
        std::vector<
            std::reference_wrapper<PacketType>
        > types;
    public:
        PacketsRegister(const PacketsRegister&) = delete;
        PacketsRegister operator=(const PacketsRegister&) = delete;
    };
}