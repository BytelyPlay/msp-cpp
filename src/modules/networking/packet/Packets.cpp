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
void Packets::PacketsRegister::receivedPacket(
    std::vector<unsigned char> data,
    MinecraftServer& server,
    MinecraftProtocol& protocol,
    MinecraftClient& client)
{
    TypedInputStream in = TypedInputStream(data.data(),
        data.data() + data.size());
    auto optId = VarIntPacketCodec::getInstance().deserialize(in);
    if (!optId.has_value())
    {
        Logger::warn("Couldn't deserialize Packet ID.");
        return;
    }
    int id = optId.value();

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

            if (c2sType.deserializeAndCall(
                in,
                server,
                protocol,
                client
            ))
                Logger::warn("Couldn't deserialize and call a C2S packet.");
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