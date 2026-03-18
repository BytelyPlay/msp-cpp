module;
#include <vector>
export module PacketS2C;
import Packet;
import PacketType;

export class PacketS2C : Packet
{
public:
    PacketType& getPacketType() override = 0;
};