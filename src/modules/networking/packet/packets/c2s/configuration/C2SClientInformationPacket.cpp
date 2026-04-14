module;

module C2SClientInformationPacket;
import C2SClientInformationPacketType;

// PUBLIC
PacketType& C2SClientInformationPacket::getPacketType()
{
    return C2SClientInformationPacketType::getInstance();
}

// PUBLIC
