module;
#include <vector>
#include <string>
#include <memory>

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
std::unique_ptr<PacketC2S> C2SIntentionPacketType::deserialize(TypedInputStream& in)
{
    // START PROTOCOL VERSION
    VarIntCodec& varIntCodec = VarIntCodec::CODEC;
    std::unique_ptr<C2SIntentionPacket> packet =
        std::make_unique<C2SIntentionPacket>();

    packet->protocolVersion = varIntCodec.deserialize(in);
    // END PROTOCOL VERSION

    // START SERVER ADDRESS
    int stringLength = varIntCodec.deserialize(in);

    std::vector<unsigned char> serverAddressBytes;
    in.readBytes(stringLength, serverAddressBytes);

    serverAddressBytes.push_back(0x00);

    packet->serverAddress = std::string(
        serverAddressBytes.begin(), serverAddressBytes.end()
    );
    // END SERVER ADDRESS

    // START INTENT
    packet->intent = static_cast<C2SIntentionPacket::Intent>(
        varIntCodec.deserialize(in)
    );
    // END INTENT
    return packet;
}
// PRIVATE
C2SIntentionPacketType::C2SIntentionPacketType()
= default;
