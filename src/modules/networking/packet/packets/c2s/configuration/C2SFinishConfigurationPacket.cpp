module;


module C2SFinishConfigurationPacket;
import PacketType;
import C2SFinishConfigurationPacketType;


// PUBLIC
PacketType& C2SFinishConfigurationPacket::getPacketType()
{
    return C2SFinishConfigurationPacketType::getInstance();
}

// PUBLIC
