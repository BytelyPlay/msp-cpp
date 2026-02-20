module;
#include <vector>
export module PacketS2C;
import Packet;

export class PacketS2C : Packet
{
public:
    virtual std::vector<unsigned char> deserialize() = 0;
};