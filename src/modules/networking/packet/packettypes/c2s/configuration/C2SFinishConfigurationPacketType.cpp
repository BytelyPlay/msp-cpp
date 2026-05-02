module;
#include <string>
#include <memory>


module C2SFinishConfigurationPacketType;
import MinecraftClient;
import MinecraftProtocol;
import MinecraftServer;
import PacketParsingException;
import TypedInputStream;
import Phase;
import PacketC2S;
import C2SFinishConfigurationPacket;


// PUBLIC
C2SFinishConfigurationPacketType& C2SFinishConfigurationPacketType::getInstance()
{
    static C2SFinishConfigurationPacketType type;
    return type;
}

// PUBLIC
Phase C2SFinishConfigurationPacketType::getPhase()
{
    return CONFIGURATION;
}

int C2SFinishConfigurationPacketType::getPacketID()
{
    return 3;
}

std::string C2SFinishConfigurationPacketType::getPacketIdentifier()
{
    return "minecraft:finish_configuration";
}

// PUBLIC
std::unique_ptr<PacketC2S> C2SFinishConfigurationPacketType::deserialize(
    TypedInputStream& in
)
{
    std::unique_ptr<C2SFinishConfigurationPacket> packet =
        std::make_unique<C2SFinishConfigurationPacket>();
    return packet;
}
// PRIVATE
C2SFinishConfigurationPacketType::C2SFinishConfigurationPacketType()
= default;
