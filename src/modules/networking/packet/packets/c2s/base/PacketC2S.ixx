module;
#include <vector>

export module PacketC2S;
import Packet;

export class PacketC2S : public Packet
{
    virtual std::vector<unsigned char> deserialize() = 0;
};