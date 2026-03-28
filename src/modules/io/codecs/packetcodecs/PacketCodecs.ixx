/* module;
#include <functional>
#include <utility>
*/
export module PacketCodecs; /*
import PacketCodec;

// The Codec system is HEAVILY inspired by Minecraft.
/* TODO: Some easier way to make a codec,
like an std::function that you just give to serialize an deserialize */ /*
export class PacketCodecs
{
public:
    template<typename T>
    struct IsValidPair : std::false_type {};

    template<typename U, typename T>
    struct IsValidPair<std::pair<std::function<U(T&)>, PacketCodec<U>>>
        : std::true_type {};
public:
    template<typename T, typename... Pairs>
    requires (IsValidPair<std::decay_t<Pairs>>::value && ...)
    PacketCodec<T> createSequencedCodec(Pairs... getterAndCodec);
}; */