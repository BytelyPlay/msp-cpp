module;


export module C2SLoginAcknowledgedPacket;
import PacketC2S;
import PacketType;


export class C2SLoginAcknowledgedPacket : public PacketC2S
{
public:
    PacketType& getPacketType() override;
public:

};