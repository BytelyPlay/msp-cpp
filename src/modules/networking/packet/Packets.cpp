module;
#include <memory>
#include <string>
#include <vector>

module Packets;

import VarIntPacketCodec;
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
// TODO: Handle exceptions.
void Packets::PacketsRegister::receivedPacket(
    std::vector<unsigned char> data,
    MinecraftServer& server,
    MinecraftProtocol& protocol,
    MinecraftClient& client)
{
    TypedInputStream in = TypedInputStream(data.data(),
        data.data() + data.size());
    int id = VarIntPacketCodec::getInstance().deserialize(in);

    // TODO: Replace with std::unordered_map
    for (auto typeWrapper : types)
    {
        PacketType& type = typeWrapper.get();

        if (type.getPacketID() == id &&
            type.getPhase() ==
            client.getPhase() &&
            type.isC2S())
        {
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
// PUBLIC

// PRIVATE
Packets::PacketsRegister::PacketsRegister()
= default;

// PRIVATE
// PUBLIC