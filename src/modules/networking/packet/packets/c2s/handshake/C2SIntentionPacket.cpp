module;

module C2SIntentionPacket;
import C2SIntentionPacketType;

// PUBLIC
// PUBLIC
PacketType& C2SIntentionPacket::getPacketType()
{
    return C2SIntentionPacketType::getInstance();
}
// PUBLIC
