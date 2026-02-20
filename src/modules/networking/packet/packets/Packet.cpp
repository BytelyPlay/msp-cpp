module;

module Packet;

// PUBLIC
std::vector<unsigned char> Packet::deserialize()
{
    return getPacketType().deserialize(*this);
}
