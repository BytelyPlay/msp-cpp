module;
#include <vector>
#include <mutex>
#include <shared_mutex>
#include <unordered_map>
#include <memory>

export module PrefixedArrayPacketCodec;
import PacketCodec;
import TypedInputStream;
import TypedOutputStream;
import VarIntPacketCodec;

// TODO: To be replaced with a FIXED array packet codec...
export template<typename T>
class PrefixedArrayPacketCodec : public PacketCodec<std::vector<T>>
{
public:
    static PrefixedArrayPacketCodec& getInstance(PacketCodec<T>& codec);

    void serialize(
        const std::vector<T>& obj,
        TypedOutputStream& out
    ) override;
    std::vector<T> deserialize(
        TypedInputStream& in
    ) override;
private:
    PacketCodec<T>& codec;
private:
    PrefixedArrayPacketCodec(PacketCodec<T>& codec);
};

// PUBLIC
template <typename T>
PrefixedArrayPacketCodec<T>& PrefixedArrayPacketCodec<T>::getInstance(PacketCodec<T>& codec)
{
    // TODO: Don't duplicate code...
    static
    std::unordered_map
    <PacketCodec<T>*, std::unique_ptr<PrefixedArrayPacketCodec>> codecInstances;

    static std::mutex codecInstancesMutex;
    std::unique_lock lock(codecInstancesMutex);

    codecInstances.try_emplace
    (&codec,
        std::move
        (std::unique_ptr
            <PrefixedArrayPacketCodec>
            (new PrefixedArrayPacketCodec(codec))));

    return *codecInstances.find(&codec)->second.get();
}
template <typename T>
void PrefixedArrayPacketCodec<T>::serialize(const std::vector<T>& objVec, TypedOutputStream& out)
{
    VarIntPacketCodec& varIntCodec =
        VarIntPacketCodec::getInstance();
    varIntCodec.serialize(objVec.size(), out);

    for (T obj : objVec)
        codec.serialize(obj, out);
}

template <typename T>
std::vector<T> PrefixedArrayPacketCodec<T>::deserialize(TypedInputStream& in)
{
    VarIntPacketCodec& varIntCodec =
        VarIntPacketCodec::getInstance();

    int length = varIntCodec.deserialize(in);
    std::vector<T> result;

    for (int i = 0; i < length; i++)
        result.push_back(codec.deserialize(in));
    return result;
}
// PRIVATE
template <typename T>
PrefixedArrayPacketCodec<T>::PrefixedArrayPacketCodec(PacketCodec<T>& codec)
: codec(codec)
{
}
// PRIVATE