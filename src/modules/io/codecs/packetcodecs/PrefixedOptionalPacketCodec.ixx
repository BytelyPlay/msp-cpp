module;
#include <optional>
#include <unordered_map>
#include <shared_mutex>
#include <mutex>
#include <memory>

export module PrefixedOptionalPacketCodec;
import PacketCodec;
import TypedInputStream;
import TypedOutputStream;
import CodecParsingException;

export template<typename T>
class PrefixedOptionalPacketCodec : public PacketCodec<std::optional<T>>
{
public:
    static PrefixedOptionalPacketCodec& getInstance(PacketCodec<T>& codec);

    void serialize(
        const std::optional<T>& opt,
        TypedOutputStream& out
    ) override;
    std::optional<T> deserialize(
        TypedInputStream& in
    ) override;
public:
private:
    PrefixedOptionalPacketCodec(PacketCodec<T>& codec);
private:
    PacketCodec<T>& codec;
};
// PUBLIC
template <typename T>
PrefixedOptionalPacketCodec<T>&
    PrefixedOptionalPacketCodec<T>::getInstance(PacketCodec<T>& codec)
{
    // TODO: Don't duplicate code...
    static
    std::unordered_map
    <PacketCodec<T>*, std::unique_ptr<PrefixedOptionalPacketCodec>> codecInstances;

    static std::mutex codecInstancesMutex;
    std::unique_lock lock(codecInstancesMutex);

    codecInstances.try_emplace
    (&codec,
        std::move
        (std::unique_ptr
            <PrefixedOptionalPacketCodec>
            (new PrefixedOptionalPacketCodec(codec))));

    return *codecInstances.find(&codec)->second.get();
}
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
        codec.serialize(opt.value(), out);
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
// PRIVATE
template <typename T>
PrefixedOptionalPacketCodec<T>::PrefixedOptionalPacketCodec(PacketCodec<T>& codec)
: codec(codec)
{

}
// PRIVATE