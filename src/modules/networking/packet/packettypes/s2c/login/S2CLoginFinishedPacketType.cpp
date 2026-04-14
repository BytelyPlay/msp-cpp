module;
#include <cassert>
#include <vector>
#include <memory>

module S2CLoginFinishedPacketType;
import S2CLoginFinishedPacket;
import GameProfile;
import GameProfilePacketCodec;

// PUBLIC
S2CLoginFinishedPacketType& S2CLoginFinishedPacketType::getInstance()
{
    static S2CLoginFinishedPacketType type;
    return type;
}

// PUBLIC
void S2CLoginFinishedPacketType::serialize
(
    std::unique_ptr<PacketS2C> basePacket,
    TypedOutputStream& out,
    bool& successful
)
{
    assert(dynamic_cast<S2CLoginFinishedPacket*>(basePacket.get()));
    GameProfilePacketCodec& gameProfileCodec = GameProfilePacketCodec::getInstance();

    auto* packetPtr =
        static_cast<S2CLoginFinishedPacket*>
    (basePacket.get());
    S2CLoginFinishedPacket& packet = *packetPtr;

    gameProfileCodec.serialize(packet.profile, out, successful);
}

// PUBLIC
int S2CLoginFinishedPacketType::getPacketID()
{
    return 0x02;
}

std::string S2CLoginFinishedPacketType::getPacketIdentifier()
{
    return "minecraft:login_finished";
}

Phase S2CLoginFinishedPacketType::getPhase()
{
    return LOGIN;
}
// PRIVATE
S2CLoginFinishedPacketType::S2CLoginFinishedPacketType()
= default;

// PUBLIC
