module;
#include <functional>
#include <sys/types.h>
#include <cstdint>
#include <memory>
module PacketTypeC2S;

// PUBLIC
void PacketTypeC2S::deserializeAndCallIfPresent(
    TypedInputStream& in, MinecraftServer& server,
    MinecraftProtocol& protocol, MinecraftClient& client
)
{
    auto packet = deserialize(in);
    callListener(std::move(packet), server, protocol, client);
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
std::unique_ptr<PacketC2S> PacketTypeC2S::deserialize(std::vector<unsigned char> bytes, uint& bytesConsumed)
{
    TypedInputStream in(bytes.data(),
        bytes.data() + bytes.size());
    std::unique_ptr<PacketC2S> packet = deserialize(in);

    bytesConsumed = in.getBytesConsumed();
    return packet;
}
