module;
#include <string>
#include <memory>
#include <vector>

module C2SCustomPayloadPacketType;
import VarIntPacketCodec;
import MinecraftClient;
import MinecraftProtocol;
import MinecraftServer;
import PacketParsingException;
import TypedInputStream;
import Phase;
import PacketC2S;
import C2SCustomPayloadPacket;
import Identifier;
import IdentifierPacketCodec;
import CodecParsingException;

// PUBLIC
C2SCustomPayloadPacketType& C2SCustomPayloadPacketType::getInstance()
{
    static C2SCustomPayloadPacketType type;
    return type;
}

// PUBLIC
Phase C2SCustomPayloadPacketType::getPhase()
{
    return CONFIGURATION;
}

int C2SCustomPayloadPacketType::getPacketID()
{
    return 2;
}

std::string C2SCustomPayloadPacketType::getPacketIdentifier()
{
    return "minecraft:custom_payload";
}

// PUBLIC
std::unique_ptr<PacketC2S> C2SCustomPayloadPacketType::deserialize(TypedInputStream& in)
{
    std::unique_ptr<C2SCustomPayloadPacket> packet =
        std::make_unique<C2SCustomPayloadPacket>();
    packet->channel = IdentifierPacketCodec
    ::getInstance()
    .deserialize(in);
    
    std::vector<unsigned char> allBytesRemaining;

    if (in.readBytes(in.getBytesLeft(), allBytesRemaining)
        < in.getBytesLeft())
        throw CodecParsingException(
            "Couldn't fully read payload "
            "in custom payload packet."
        );
    packet->data = allBytesRemaining;
    return packet;
}
// PRIVATE
C2SCustomPayloadPacketType::C2SCustomPayloadPacketType()
= default;
