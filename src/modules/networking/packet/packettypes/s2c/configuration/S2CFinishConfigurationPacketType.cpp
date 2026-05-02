module;
#include <cassert>
#include <memory>

module S2CFinishConfigurationPacketType;
import VarIntPacketCodec;
import MinecraftClient;
import MinecraftProtocol;
import MinecraftServer;
import PacketParsingException;
import TypedOutputStream;
import Phase;
import S2CFinishConfigurationPacket;
// PUBLIC
S2CFinishConfigurationPacketType& S2CFinishConfigurationPacketType::getInstance()
{
    static S2CFinishConfigurationPacketType type;
    return type;
}

// PUBLIC
void S2CFinishConfigurationPacketType::serialize
(
    std::unique_ptr<PacketS2C> basePacket,
    TypedOutputStream& out
)
{
    assert(dynamic_cast<S2CFinishConfigurationPacket*>(basePacket.get()));
}

// PUBLIC
int S2CFinishConfigurationPacketType::getPacketID()
{
    return 3;
}

std::string S2CFinishConfigurationPacketType::getPacketIdentifier()
{
    return "minecraft:finish_configuration";
}

Phase S2CFinishConfigurationPacketType::getPhase()
{
    return CONFIGURATION;
}
// PRIVATE
S2CFinishConfigurationPacketType::S2CFinishConfigurationPacketType()
= default;

// PUBLIC
