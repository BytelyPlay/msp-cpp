module;
#include <memory>

module C2SLoginStartPacketType;

// PUBLIC
std::unique_ptr<PacketC2S> C2SLoginStartPacketType::deserialize(TypedInputStream& in)
{
    auto packet = std::make_unique
}

// PRIVATE
C2SLoginStartPacketType::C2SLoginStartPacketType()
= default;
// PUBLIC
