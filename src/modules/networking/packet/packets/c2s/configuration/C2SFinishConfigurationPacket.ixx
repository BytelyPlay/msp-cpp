module;


export module C2SFinishConfigurationPacket;
import PacketC2S;
import PacketType;


export class C2SFinishConfigurationPacket : public PacketC2S
{
public:
    PacketType& getPacketType() override;
public:

};