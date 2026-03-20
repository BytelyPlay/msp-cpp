module;

export module S2CLoginFinishedPacket;
import PacketS2C;
import PacketType;

export class S2CLoginFinishedPacket : public PacketS2C
{
public:
    PacketType& getPacketType() override;
};