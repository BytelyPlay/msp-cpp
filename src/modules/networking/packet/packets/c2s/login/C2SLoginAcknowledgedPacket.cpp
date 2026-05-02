module;


module C2SLoginAcknowledgedPacket;
import PacketType;
import C2SLoginAcknowledgedPacketType;


// PUBLIC
PacketType& C2SLoginAcknowledgedPacket::getPacketType()
{
    return C2SLoginAcknowledgedPacketType::getInstance();
}

// PUBLIC
