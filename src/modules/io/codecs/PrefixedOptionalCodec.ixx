module;
#include <vector>
#include <string>
#include <cstdint>
#include <optional>

export module PrefixedOptionalCodec;
import Codec;
import TypedInputStream;
import TypedOutputStream;

export template<typename T>
/* This Codec is a bit of an exception,
since you're supposed to initialize it. And then reuse it...
and it also doesn't inherit from Codec, due to it having requirements that force that.

TODO: Replace with a MapCodec-like thing or something,
point is, a subclass of Codec... Or not just yeah
There is a possibility that this is just an exception
that won't be a subclass...
maybe it's best that way
*/

class PrefixedOptionalCodec
{
public:
    void serialize(
        const std::optional<T>& opt,
        Codec<T>& codec,
        TypedOutputStream& out
    );
    std::optional<T> deserialize(
        TypedInputStream& in,
        Codec<T>& codec
    );
public:
    std::vector<unsigned char> serialize(
        const std::optional<T>& opt,
        Codec<T>& codec
    );
    T deserialize(
        const std::vector<unsigned char>& data,
        Codec<T>& codec,

        uint& bytesConsumed
    );
};
