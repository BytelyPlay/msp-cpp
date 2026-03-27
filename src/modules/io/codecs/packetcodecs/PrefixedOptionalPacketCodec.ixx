module;
#include <vector>
#include <string>
#include <cstdint>
#include <optional>

export module PrefixedOptionalPacketCodec;
import PacketCodec;
import TypedInputStream;
import TypedOutputStream;

export template<typename T>
/*
TODO: Replace with the pattern, where it
also uses a template. But the Codec is set at construction...
This HAS to be a subclass of PacketCodec
*/

/* export */ class PrefixedOptionalPacketCodec
{
public:
    void serialize(
        const std::optional<T>& opt,
        PacketCodec<T>& codec ,
        TypedOutputStream& out
    );
    std::optional<T> deserialize(
        TypedInputStream& in,
        PacketCodec <T>& codec
    );
public:
    std::vector<unsigned char> serialize(
        const std::optional<T>& opt,
        PacketCodec<T>& codec
    );
    T deserialize(
        const std::vector<unsigned char>& data,
        PacketCodec<T>& codec,

        uint& bytesConsumed
    );
};
