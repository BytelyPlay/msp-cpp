module;
#include <vector>
#include <optional>
#include <cstdint>
#include <sys/types.h>
#include <unordered_map>
#include <shared_mutex>
#include <mutex>

module PrefixedOptionalPacketCodec;
import CodecParsingException;

// PUBLIC
template <typename T>
void PrefixedOptionalPacketCodec<T>::serialize(
    const std::optional<T>& opt,
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

PrefixedOptionalPacketCodec<T>::deserialize(
    TypedInputStream& in
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
std::vector<unsigned char> PrefixedOptionalPacketCodec<T>::serialize(
    const std::optional<T>& opt,
    PacketCodec<T>& codec
)
{
    TypedOutputStream out;
    serialize(opt, codec, out);

    return out.getData();
}

template <typename T>
T PrefixedOptionalPacketCodec<T>::deserialize(
    const std::vector<unsigned char>& data,
    PacketCodec<T>& codec,

    uint& bytesConsumed
)
{
    TypedInputStream in(data.data(),
    data.data() + data.size());

    T val = deserialize(in);
    bytesConsumed = in.getBytesConsumed();

    return val;
}
// PRIVATE
template <typename T>
PrefixedOptionalPacketCodec<T>::PrefixedOptionalPacketCodec(PacketCodec<T>& codec)
: codec(codec)
{

}

// PRIVATE
