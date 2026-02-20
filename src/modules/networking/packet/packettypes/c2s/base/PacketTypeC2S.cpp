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
