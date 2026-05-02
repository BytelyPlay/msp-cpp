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
import C2SIntentionPacketType;
import S2CLoginFinishedPacketType;
import C2SLoginStartPacketType;
import C2SClientInformationPacketType;
import C2SCustomPayloadPacketType;
import C2SFinishConfigurationPacketType;

#define DEFINE_PACKET(variableName, type) \
        const auto& variableName = \
        Packets::PacketsRegister::getInstance() \
        .registerPacket(type);

// TODO: Read from a reports/packets.json and use the identifier to get the protocol ID.
export namespace Packets
{
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
    public:
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
        T& registerPacket(T& type);
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

    namespace S2C
    {
        DEFINE_PACKET(S2C_LOGIN_FINISHED_PACKET,
            S2CLoginFinishedPacketType::getInstance());
    }
    namespace C2S
    {
        DEFINE_PACKET(
            C2S_INTENTION_PACKET,
            C2SIntentionPacketType::getInstance()
        );
        DEFINE_PACKET(
            C2S_LOGIN_START_PACKET,
            C2SLoginStartPacketType::getInstance()
        );
        DEFINE_PACKET(
            C2S_CLIENT_INFORMATION_PACKET,
            C2SClientInformationPacketType::getInstance()
        );
        DEFINE_PACKET(
            C2S_CUSTOM_PAYLOAD_PACKET,
            C2SCustomPayloadPacketType::getInstance()
        )
        DEFINE_PACKET(
            C2S_FINISH_CONFIGURATION_PACKET,
            C2SFinishConfigurationPacketType::getInstance()
        )
    }
}

// PUBLIC
// PUBLIC
// PUBLIC
template <typename T>
T& Packets::PacketsRegister::registerPacket(T& type)
{
    static_assert(std::is_base_of_v<PacketType, T>);

    types.push_back(type);
    return type;
}
// PRIVATE
// PRIVATE
// PUBLIC