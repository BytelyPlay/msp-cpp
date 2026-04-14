module;
#include <functional>
#include <sys/types.h>
#include <cstdint>
#include <memory>
module PacketTypeC2S;

// PUBLIC
bool PacketTypeC2S::deserializeAndCall(
    TypedInputStream& in, MinecraftServer& server,
    MinecraftProtocol& protocol, MinecraftClient& client
)
{
    auto packet = deserialize(in);
    if (!packet.has_value()) return false;
    callListener(std::move(
        packet.value()), server,
        protocol, client
    );

    return true;
}
// PUBLIC
void PacketTypeC2S::setListener(std::function<void(std::unique_ptr<PacketC2S>,
    MinecraftServer&,
    MinecraftProtocol&,
    MinecraftClient&)> listener)
{
    this->listener = listener;
}

void PacketTypeC2S::callListener(std::unique_ptr<PacketC2S> packet, MinecraftServer& server,
    MinecraftProtocol& protocol,
    MinecraftClient& client)
{
    listener(std::move(packet), server, protocol, client);
}
// PUBLIC
bool PacketTypeC2S::isC2S()
{
    return true;
}
// PUBLIC
std::optional<std::unique_ptr<PacketC2S>> PacketTypeC2S::deserialize(
    std::vector<unsigned char> bytes, uint& bytesConsumed
)
{
    TypedInputStream in(bytes.data(),
        bytes.data() + bytes.size());
    auto packet = deserialize(in);

    bytesConsumed = in.getBytesConsumed();
    return packet;
}
