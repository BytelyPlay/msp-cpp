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
import PacketParsingException;
import ChatMode;
import MainHand;
import ParticleStatus;

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

    packet->locale = stringCodec.deserialize(in);

    in.readOrThrow(packet->viewDistance,
        "Couldn't deserialize view distance.");

    packet->chatMode = static_cast<ChatMode>(varIntCodec.deserialize(in));

    in.readOrThrow(packet->chatColors,
        "Couldn't deserialize chat colors.");

    in.readOrThrow(packet->displayedSkinParts,
        "Couldn't deserialize displayed skin parts.");

    packet->mainHand =
        static_cast<MainHand>(varIntCodec.deserialize(in));

    in.readOrThrow(packet->allowServerListings,
        "Couldn't deserialize allow server listings.");

    packet->particleStatus =
        static_cast<ParticleStatus>(varIntCodec.deserialize(in));
    return std::move(packet);
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
= default;
// PUBLIC
