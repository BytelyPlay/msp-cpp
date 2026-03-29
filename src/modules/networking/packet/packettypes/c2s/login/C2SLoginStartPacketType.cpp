module;
#include <memory>
#include <string>

module C2SLoginStartPacketType;
import C2SLoginStartPacket;
import StringPacketCodec;
import UUID;
import UUIDPacketCodec;
// PUBLIC
C2SLoginStartPacketType& C2SLoginStartPacketType::getInstance()
{
    static C2SLoginStartPacketType type;
    return type;
}

std::unique_ptr<PacketC2S> C2SLoginStartPacketType::deserialize(TypedInputStream& in)
{
    auto packet = std::make_unique<C2SLoginStartPacket>();

    StringPacketCodec& stringCodec = StringPacketCodec::getInstance();
    UUIDPacketCodec& uuidCodec = UUIDPacketCodec::getInstance();

    packet->username = stringCodec.deserialize(in);
    packet->uuid = uuidCodec.deserialize(in);
}
// PUBLIC
// PRIVATE
C2SLoginStartPacketType::C2SLoginStartPacketType()
= default;
// PUBLIC
