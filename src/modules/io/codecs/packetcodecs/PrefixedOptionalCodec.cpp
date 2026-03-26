module;
#include <vector>
#include <optional>
#include <cstdint>
#include <sys/types.h>

module PrefixedOptionalCodec;
import CodecParsingException;

// PUBLIC
template <typename T>
void PrefixedOptionalCodec<T>::serialize(
    const std::optional<T>& opt,
    Codec<T>& codec,
    TypedOutputStream& out
)
{
    if (!opt.has_value())
    {
        out << false;
    } else
    {
        out << true;
        out << codec.serialize(opt.value());
    }
}

template <typename T>
std::optional<T>

PrefixedOptionalCodec<T>::deserialize(
    TypedInputStream& in,
    Codec<T>& codec
)
{
    bool hasValue;
    if (!(in >> hasValue))
        throw CodecParsingException("Couldn't check a boolean.");

    if (!hasValue) return {};

    T obj = codec.deserialize(in);
    return obj;
}
// PUBLIC
template <typename T>
std::vector<unsigned char> PrefixedOptionalCodec<T>::serialize(
    const std::optional<T>& opt,
    Codec<T>& codec
)
{
    TypedOutputStream out;
    serialize(opt, codec, out);

    return out.getData();
}

template <typename T>
T PrefixedOptionalCodec<T>::deserialize(
    const std::vector<unsigned char>& data,
    Codec<T>& codec,

    uint& bytesConsumed
)
{
    TypedInputStream in(data.data(),
    data.data() + data.size());

    T val = deserialize(in, codec);
    bytesConsumed = in.getBytesConsumed();

    return val;
}
