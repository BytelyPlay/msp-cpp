module;
#include <string>

export module C2SLoginStartPacket;
import PacketC2S;
import PacketType;
import UUID;

export class C2SLoginStartPacket : public PacketC2S
{
public:
    PacketType& getPacketType() override;
public:
    std::string username {};
    UUID uuid {};
};
