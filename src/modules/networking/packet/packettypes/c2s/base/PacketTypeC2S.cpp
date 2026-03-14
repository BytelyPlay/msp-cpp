module;
#include <functional>
#include <sys/types.h>
#include <cstdint>
module PacketTypeC2S;

// PUBLIC
void PacketTypeC2S::deserializeAndCall(
    TypedInputStream& in, MinecraftServer& server,
    MinecraftProtocol& protocol, MinecraftClient& client
)
{
    auto& packet = deserialize(in);
    callListener(packet, server, protocol, client);
}
// PUBLIC
void PacketTypeC2S::setListener(std::function<void(PacketC2S&,
    MinecraftServer&,
    MinecraftProtocol&,
    MinecraftClient&)> listener)
{
    this->listener = listener;
}

void PacketTypeC2S::callListener(PacketC2S& packet, MinecraftServer& server,
    MinecraftProtocol& protocol,
    MinecraftClient& client)
{
    listener(packet, server, protocol, client);
}
// PUBLIC
bool PacketTypeC2S::isC2S()
{
    return true;
}
// PUBLIC
PacketC2S& PacketTypeC2S::deserialize(std::vector<unsigned char> bytes, uint& bytesConsumed)
{
    TypedInputStream in(bytes.data(),
        bytes.data() + bytes.size());
    PacketC2S& packet = deserialize(in);

    bytesConsumed = in.getBytesConsumed();
    return packet;
}
