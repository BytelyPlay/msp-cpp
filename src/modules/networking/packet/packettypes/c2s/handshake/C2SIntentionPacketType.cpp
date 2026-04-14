module;
#include <vector>
#include <string>
#include <memory>

module C2SIntentionPacketType;
import VarIntPacketCodec;
import MinecraftClient;
import MinecraftProtocol;
import MinecraftServer;
import PacketParsingException;

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
    VarIntPacketCodec& varIntCodec = VarIntPacketCodec::getInstance();
    std::unique_ptr<C2SIntentionPacket> packet =
        std::make_unique<C2SIntentionPacket>();

    packet->protocolVersion = varIntCodec.deserialize(in);
    // END PROTOCOL VERSION

    // START SERVER ADDRESS
    int stringLength = varIntCodec.deserialize(in);

    std::vector<unsigned char> serverAddressBytes;
    in.readBytes(stringLength, serverAddressBytes);

    packet->serverAddress = std::string(
        serverAddressBytes.begin(), serverAddressBytes.end()
    );
    // END SERVER ADDRESS
    // START SERVER PORT
    if (!(in >> packet->serverPort))
        throw PacketParsingException("Couldn't read serverPort, possible EoF");
    // END SERVER PORT
    // START INTENT
    packet->intent = static_cast<C2SIntentionPacket::Intent>(
        varIntCodec.deserialize(in)
    );
    // END INTENT
    return packet;
}
// PRIVATE
C2SIntentionPacketType::C2SIntentionPacketType()
{
    this->setListener([](
    std::unique_ptr<PacketC2S> basePacket,
    MinecraftServer&,
    MinecraftProtocol&,
    MinecraftClient& client)
{
    auto* packet = static_cast<C2SIntentionPacket*>(basePacket.get());

    if (packet->intent == C2SIntentionPacket::LOGIN)
    {
        client.setPhase(LOGIN);
    } else if (packet->intent == C2SIntentionPacket::STATUS)
    {
        client.setPhase(STATUS);
    } else if (packet->intent == C2SIntentionPacket::TRANSFER)
    {
        client.disconnect("Transferring is currently not supported.");
    }
});
}
