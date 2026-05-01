module;
#include <vector>

export module C2SCustomPayloadPacket;
import PacketC2S;
import PacketType;
import Identifier;

export class C2SCustomPayloadPacket : public PacketC2S
{
public:
    PacketType& getPacketType() override;
public:
    Identifier channel;
    std::vector<unsigned char> data;
};