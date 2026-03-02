module;
#include <string>

module Packets;
import VarIntCodec;

// Packets::PacketRegister
// PUBLIC

Packets::PacketsRegister& Packets::PacketsRegister::getInstance()
{
    static PacketsRegister packetsRegister;
    return packetsRegister;
}
// PUBLIC
void Packets::PacketsRegister::receivedPacket(std::vector<unsigned char> data)
{
    uint bytesConsumed = 0;

    int id = VarIntCodec::CODEC.deserialize(data, bytesConsumed);
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
// PRIVATE
// PUBLIC