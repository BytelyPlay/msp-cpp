module;
#include <memory>
#include <string>
#include <vector>

module Packets;

import VarIntCodec;
import TypedInputStream;
import Logger;
import PacketTypeC2S;
import PacketC2S;
import MinecraftServer;
import MinecraftProtocol;
import MinecraftClient;

// Packets::PacketRegister
// PUBLIC

Packets::PacketsRegister& Packets::PacketsRegister::getInstance()
{
    static PacketsRegister packetsRegister;
    return packetsRegister;
}
// PUBLIC
void Packets::PacketsRegister::receivedPacket(
    std::vector<unsigned char> data,
    MinecraftServer& server,
    MinecraftProtocol& protocol,
    MinecraftClient& client)
{
    TypedInputStream in = TypedInputStream(data.data(),
        data.data() + data.size());
    int id = VarIntCodec::CODEC.deserialize(in);

    for (auto typeWrapper : types)
    {
        PacketType& type = typeWrapper.get();

        if (type.getPacketID() == id &&
            type.getPhase() ==
            client.getPhase())
        {
            if (!type.isC2S())
            {
                Logger::warn("Discarding packet: " +
                    type.getPacketIdentifier() +
                    " because it is an S2C packet sent to the server.");
                return;
            }
            // Type is a PacketTypeC2S
            auto& c2sType = static_cast<PacketTypeC2S&>(type);
            c2sType.deserializeAndCall(
                in,
                server,
                protocol,
                client
            );
            return;
        }
    }
    Logger::warn("No Packet Type found for packet ID: " +
        std::to_string(id) + " in phase: " + std::to_string(client.getPhase()));
}
// PRIVATE
template <typename T>
T Packets::PacketsRegister::registerPacket(T type)
{
    static_assert(std::is_base_of_v<PacketType, T>);

    types.push_back(type);
    return type;
}

// PRIVATE
Packets::PacketsRegister::PacketsRegister()
= default;

// PRIVATE
// PUBLIC