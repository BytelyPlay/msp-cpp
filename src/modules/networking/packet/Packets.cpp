module;
#include <string>

module Packets;

import VarIntCodec;
import TypedInputStream;
import Logger;
import PacketTypeC2S;
import PacketC2S;
import MinecraftServer;
import MinecraftProtocol;

// Packets::PacketRegister
// PUBLIC

Packets::PacketsRegister& Packets::PacketsRegister::getInstance()
{
    static PacketsRegister packetsRegister;
    return packetsRegister;
}
// PUBLIC
void Packets::PacketsRegister::receivedPacket(std::vector<unsigned char> data,
    MinecraftServer server,
    MinecraftProtocol protocol)
{
    uint bytesConsumed = 0;

    TypedInputStream in = TypedInputStream(data.data(),
        data.data() + data.size());
    int id = VarIntCodec::CODEC.deserialize(in);

    for (auto typeWrapper : types)
    {
        PacketType& type = typeWrapper.get();

        if (type.getPacketID() == id)
        {
            if (!type.isC2S())
            {
                Logger::warn("Discarding packet: " +
                    type.getPacketIdentifier() +
                    " because it is an S2C packet sent to the server.");
                break;
            }
            // Type is a PacketTypeC2S
            PacketTypeC2S<PacketC2S>& c2sType = static_cast<PacketTypeC2S&>(type);
            c2sType.callListener(
                c2sType.deserialize(in),
                server,
                protocol
            );
            break;
        }
    }
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