module;
#include <vector>

export module PacketC2S;
import Packet;
import PacketType;

export class PacketC2S : public Packet
{
public:
    PacketType& getPacketType() override = 0;
};