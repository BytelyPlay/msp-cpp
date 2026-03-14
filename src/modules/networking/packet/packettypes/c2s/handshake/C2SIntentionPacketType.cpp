module;
#include <vector>
#include <string>
#include <memory>
#include <sys/stat.h>

module C2SIntentionPacketType;
import VarIntCodec;

// PUBLIC
C2SIntentionPacketType& C2SIntentionPacketType::getInstance()
{
    static C2SIntentionPacketType type;
    return type;
}

// PUBLIC
Phase C2SIntentionPacketType::getPhase()
{
    return HANDSHAKE;
}

int C2SIntentionPacketType::getPacketID()
{
    return 0x00;
}

std::string C2SIntentionPacketType::getPacketIdentifier()
{
    return "minecraft:intention";
}

// PUBLIC
PacketC2S& C2SIntentionPacketType::deserialize(TypedInputStream& in)
{
    // START PROTOCOL VERSION
    VarIntCodec& varIntCodec = VarIntCodec::CODEC;
    C2SIntentionPacket packet;

    packet.protocolVersion = varIntCodec.deserialize(in);
    // END PROTOCOL VERSION

    // START SERVER ADDRESS
    int stringLength = varIntCodec.deserialize(in);

    std::vector<unsigned char> serverAddressBytes;
    in.readBytes(stringLength, serverAddressBytes);

    serverAddressBytes.push_back(0x00);

    packet.serverAddress = std::string(
        serverAddressBytes.begin(), serverAddressBytes.end()
    );
    // END SERVER ADDRESS

    // START INTENT
    packet.intent = static_cast<C2SIntentionPacket::Intent>(
        varIntCodec.deserialize(in)
    );
    // END INTENT
    return static_cast
    <PacketC2S&>
    (packet);
}
// PRIVATE
C2SIntentionPacketType::C2SIntentionPacketType()
= default;
