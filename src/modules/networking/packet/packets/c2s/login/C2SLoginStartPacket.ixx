module;

export module C2SLoginStartPacket;
import PacketC2S;
import PacketType;

export class C2SLoginStartPacket : public PacketC2S
{
public:
    PacketType& getPacketType() override;
public:
};
