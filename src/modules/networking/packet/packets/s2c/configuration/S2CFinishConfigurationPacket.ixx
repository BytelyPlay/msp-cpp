module;

export module S2CFinishConfigurationPacket;
import PacketS2C;
import PacketType;

export class S2CFinishConfigurationPacket : public PacketS2C
{
public:
    PacketType& getPacketType() override;
public:

};