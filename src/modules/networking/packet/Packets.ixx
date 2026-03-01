module;
#include <string>
#include <vector>

export module Packets;
import PacketType;

#define DEFINE_PACKET(variableName, id, identifier, type) \
    const auto variableName = Packets::::registerPacket(id, identifier, type);

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
        PacketsRegister& getInstance();
    private:
        /**
        * Registers a packet.
        * @tparam T Has to be a PacketType subclass.
        * @param id Protocol Packet ID (will be replaced with the reports/packets.json thing)
        * @param identifier The stable Identifier (e.g. minecraft:example_packet)
        * @param type The Packet Type
        */
        template<typename T>
        T& registerPacket(int id, std::string identifier, T type);

        /**
        * Handles a Packet being received.
        * @param data The Data excluding the Packet Length, but including the packet ID.
        */
        void receivedPacket(std::vector<unsigned char> data);
    public:
        PacketsRegister(const PacketsRegister&) = delete;
        PacketsRegister operator=(const PacketsRegister&) = delete;
    };
}