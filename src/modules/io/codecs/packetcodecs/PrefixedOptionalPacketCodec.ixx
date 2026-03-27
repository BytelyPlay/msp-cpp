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
/* This Codec is a bit of an exception,
since you're supposed to initialize it. And then reuse it...
and it also doesn't inherit from PacketCodec , due to it having requirements that force that.

TODO: Replace with a MapCodec-like thing or something,
point is, a subclass of PacketCodec ... Or not just yeah
There is a possibility that this is just an exception
that won't be a subclass...
maybe it's best that way
*/

class PrefixedOptionalPacketCodec
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
