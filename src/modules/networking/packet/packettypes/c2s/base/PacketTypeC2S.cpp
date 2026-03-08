module;
#include <functional>
#include <sys/types.h>
#include <cstdint>
module PacketTypeC2S;

// PUBLIC

// PUBLIC
template <typename T>
void PacketTypeC2S<T>::setListener(std::function<void(T,
    MinecraftServer&,
    MinecraftProtocol&)> listener)
{
    this->listener = listener;
}

template <typename T>
void PacketTypeC2S<T>::callListener(T packet, MinecraftServer& server,
    MinecraftProtocol& protocol,
    MinecraftClient& client)
{
    listener(packet, server, protocol, client);
}

// PUBLIC
template <typename T>
bool PacketTypeC2S<T>::isC2S()
{
    return true;
}
// PUBLIC
template <typename T>
T PacketTypeC2S<T>::deserialize(std::vector<unsigned char> bytes, uint& bytesConsumed)
{
    TypedInputStream in(bytes.data(),
        bytes.data() + bytes.size());
    T packet = deserialize(in);

    bytesConsumed = in.getBytesConsumed();
    return packet;
}
