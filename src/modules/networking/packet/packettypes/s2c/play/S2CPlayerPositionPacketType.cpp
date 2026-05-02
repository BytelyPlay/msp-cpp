module;
#include <memory>
#include <cassert>

module S2CPlayerPositionPacketType;
import VarIntPacketCodec;
import MinecraftClient;
import MinecraftProtocol;
import MinecraftServer;
import PacketParsingException;
import TypedOutputStream;
import Phase;
import S2CPlayerPositionPacket;
import S2CLoginFinishedPacket;
import TeleportFlags;

// PUBLIC
S2CPlayerPositionPacketType& S2CPlayerPositionPacketType::getInstance()
{
    static S2CPlayerPositionPacketType type;
    return type;
}

// PUBLIC
void S2CPlayerPositionPacketType::serialize
(
    std::unique_ptr<PacketS2C> basePacket,
    TypedOutputStream& out
)
{
    assert(dynamic_cast<S2CPlayerPositionPacket*>(basePacket.get()));

    VarIntPacketCodec& varIntCodec = VarIntPacketCodec::getInstance();

    auto* packet =
        static_cast<S2CPlayerPositionPacket*>(basePacket.get());
    varIntCodec.serialize(packet->teleportId, out);

    out << packet->x;
    out << packet->y;
    out << packet->z;

    out << packet->velocityX;
    out << packet->velocityY;
    out << packet->velocityZ;

    out << packet->yaw;
    out << packet->pitch;

    out << packet->teleportFlags;
}

// PUBLIC
int S2CPlayerPositionPacketType::getPacketID()
{
    return 70;
}

std::string S2CPlayerPositionPacketType::getPacketIdentifier()
{
    return "minecraft:player_position";
}

Phase S2CPlayerPositionPacketType::getPhase()
{
    return PLAY;
}
// PRIVATE
S2CPlayerPositionPacketType::S2CPlayerPositionPacketType()
= default;

// PUBLIC
