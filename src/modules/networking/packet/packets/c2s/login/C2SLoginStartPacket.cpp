module;

module C2SLoginStartPacket;
import C2SLoginStartPacketType;
import Packets;
// PUBLIC
PacketType& C2SLoginStartPacket::getPacketType()
{
    return C2SLoginStartPacketType::getInstance();
}
// PUBLIC
