module;

module S2CLoginFinishedPacket;
import S2CLoginFinishedPacketType;

// PUBLIC
PacketType& S2CLoginFinishedPacket::getPacketType()
{
    return S2CLoginFinishedPacketType::getInstance();
}
