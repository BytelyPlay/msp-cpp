module;
#include <vector>
#include <mutex>
#include <shared_mutex>
#include <unordered_map>
#include <memory>
#include <optional>

export module PrefixedArrayPacketCodec;
import PacketCodec;
import TypedInputStream;
import TypedOutputStream;
import VarIntPacketCodec;
import Logger;

// TODO: To be replaced with a FIXED array packet codec...
export template<typename T>
class PrefixedArrayPacketCodec : public PacketCodec<std::vector<T>>
{
public:
    static PrefixedArrayPacketCodec& getInstance(PacketCodec<T>& codec);

    void serialize(
        const std::vector<T>& obj,
        TypedOutputStream& out,
        bool& successful
    ) override;
    std::optional<std::vector<T>> deserialize(
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
void PrefixedArrayPacketCodec<T>::serialize(const std::vector<T>& objVec,
    TypedOutputStream& out,
    bool& successful)
{
    VarIntPacketCodec& varIntCodec =
        VarIntPacketCodec::getInstance();
    varIntCodec.serialize(objVec.size(), out, successful);

    if (!successful)
    {
        Logger::warn("Couldn't serialize prefixed array size.");
        return;
    }

    for (T obj : objVec)
    {
        codec.serialize(obj, out, successful);

        if (!successful)
        {
            Logger::warn("Couldn't serialize an object in the Prefixed Array.");
            return;
        }
    }
}

template <typename T>
std::optional<std::vector<T>> PrefixedArrayPacketCodec<T>::deserialize(
    TypedInputStream& in
)
{
    VarIntPacketCodec& varIntCodec =
        VarIntPacketCodec::getInstance();

    std::optional<int> optLength = varIntCodec.deserialize(in);
    std::vector<T> result;
    if (!optLength.has_value())
    {
        Logger::warn("Couldn't deserialize length of prefixed array.");
        return {};
    }

    for (int i = 0; i < optLength.value(); i++)
    {
        auto optObj = codec.deserialize(in);
        if (!optObj.has_value())
        {
            Logger::warn(std::string("No object for index: ") + std::to_string(i));
            return {};
        }
        result.push_back(optObj.value());
    }
    return result;
}
// PRIVATE
template <typename T>
PrefixedArrayPacketCodec<T>::PrefixedArrayPacketCodec(PacketCodec<T>& codec)
: codec(codec)
{
}
// PRIVATE