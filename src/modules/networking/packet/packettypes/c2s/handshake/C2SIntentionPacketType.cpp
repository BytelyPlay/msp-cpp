module;
#include <vector>
#include <string>
#include <memory>

module C2SIntentionPacketType;
import VarIntPacketCodec;
import MinecraftClient;
import MinecraftProtocol;
import MinecraftServer;
import Logger;
import StringPacketCodec;

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
std::optional<std::unique_ptr<PacketC2S>>
C2SIntentionPacketType::deserialize(TypedInputStream& in)
{
    // START PROTOCOL VERSION
    VarIntPacketCodec& varIntCodec = VarIntPacketCodec::getInstance();
    StringPacketCodec& stringCodec = StringPacketCodec::getInstance();

    std::unique_ptr<C2SIntentionPacket> packet =
        std::make_unique<C2SIntentionPacket>();

    auto optProtocolVersion = varIntCodec.deserialize(in);
    if (!optProtocolVersion.has_value()) return {};
    packet->protocolVersion = optProtocolVersion.value();
    // END PROTOCOL VERSION

    // START SERVER ADDRESS
    std::optional<std::string> optString = stringCodec.deserialize(in);
    if (!optString.has_value())
    {
        Logger::warn("Unable to read string in server address during handshake.");
        return {};
    }

    packet->serverAddress = optString.value();
    // END SERVER ADDRESS
    // START SERVER PORT
    if (!(in >> packet->serverPort))
    {
        Logger::warn("Couldn't read serverPort, possible EoF");
        return {};
    }
    // END SERVER PORT
    // START INTENT
    auto optIntentInt = varIntCodec.deserialize(in);
    if (!optIntentInt.has_value())
    {
        Logger::warn("Unable to parse int for intent.");
        return {};
    }
    packet->intent = static_cast<C2SIntentionPacket::Intent>(
        optIntentInt.value()
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
