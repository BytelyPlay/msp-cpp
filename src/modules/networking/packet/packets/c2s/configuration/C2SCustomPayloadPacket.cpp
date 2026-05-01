module;


module C2SCustomPayloadPacket;
import PacketType;
import C2SCustomPayloadPacketType;


// PUBLIC
PacketType& C2SCustomPayloadPacket::getPacketType()
{
    return C2SCustomPayloadPacketType::getInstance();
}

// PUBLIC
