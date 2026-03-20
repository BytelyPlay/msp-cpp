module;

module S2CLoginFinishedPacketType;
import S2CLoginFinishedPacket;
#include <assert.h>

// PUBLIC
S2CLoginFinishedPacketType& S2CLoginFinishedPacketType::getInstance()
{
    static S2CLoginFinishedPacketType type;
    return type;
}

// PUBLIC
std::vector<unsigned char> S2CLoginFinishedPacketType::serialize
(std::unique_ptr<PacketS2C> basePacket)
{
    assert(dynamic_cast<S2CLoginFinishedPacket*>(basePacket.get()));

    S2CLoginFinishedPacket* packetPtr =
        static_cast<S2CLoginFinishedPacket*>(basePacket.get());
    S2CLoginFinishedPacket& packet = *packetPtr;


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
