module;


module S2CPlayerPositionPacket;
import PacketType;
import S2CPlayerPositionPacketType;


// PUBLIC
PacketType& S2CPlayerPositionPacket::getPacketType()
{
    return S2CPlayerPositionPacketType::getInstance();
}

// PUBLIC