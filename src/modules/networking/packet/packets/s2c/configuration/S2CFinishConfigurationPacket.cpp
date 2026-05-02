module;


module S2CFinishConfigurationPacket;
import PacketType;
import S2CFinishConfigurationPacketType;


// PUBLIC
PacketType& S2CFinishConfigurationPacket::getPacketType()
{
    return S2CFinishConfigurationPacketType::getInstance();
}

// PUBLIC