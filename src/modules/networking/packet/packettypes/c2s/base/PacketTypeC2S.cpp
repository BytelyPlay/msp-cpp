module;
#include <functional>

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
void PacketTypeC2S<T>::callListener(T packet, MinecraftServer& server, MinecraftProtocol& protocol)
{
    listener(packet, server, protocol);
}

// PUBLIC
template <typename T>
bool PacketTypeC2S<T>::isC2S()
{
    return true;
}
