module;
#include <memory>
#include <string>

module C2SClientInformationPacketType;
import C2SClientInformationPacket;
import StringPacketCodec;
import UUID;
import UUIDPacketCodec;
import S2CLoginFinishedPacket;
import GameProfile;
import MinecraftClient;
import MinecraftServer;
import MinecraftProtocol;
import Logger;
import VarIntPacketCodec;

// PUBLIC
C2SClientInformationPacketType& C2SClientInformationPacketType::getInstance()
{
    static C2SClientInformationPacketType type;
    return type;
}

std::unique_ptr<PacketC2S> C2SClientInformationPacketType::deserialize(TypedInputStream& in)
{
    auto packet = std::make_unique<C2SClientInformationPacket>();

    StringPacketCodec& stringCodec = StringPacketCodec::getInstance();
    UUIDPacketCodec& uuidCodec = UUIDPacketCodec::getInstance();
    VarIntPacketCodec& varIntCodec = VarIntPacketCodec::getInstance();
}
// PUBLIC
Phase C2SClientInformationPacketType::getPhase()
{
    return CONFIGURATION;
}

int C2SClientInformationPacketType::getPacketID()
{
    return 0x00;
}

std::string C2SClientInformationPacketType::getPacketIdentifier()
{
    return "minecraft:client_information";
}

// PRIVATE
C2SClientInformationPacketType::C2SClientInformationPacketType()
{
    this->setListener([](
        std::unique_ptr<PacketC2S> packet,
        MinecraftServer& server,
        MinecraftProtocol& protocol,
        MinecraftClient& client
    )
    {
        Logger::debug("Received C2SClientInformationPacketType");
    });
}
// PUBLIC
