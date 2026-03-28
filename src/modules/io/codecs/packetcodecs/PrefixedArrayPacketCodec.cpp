module;
#include <mutex>
#include <shared_mutex>
#include <unordered_map>
#include <vector>

module PrefixedArrayPacketCodec;
import VarIntPacketCodec;

// PUBLIC
template <typename T>
PrefixedArrayPacketCodec<T>& PrefixedArrayPacketCodec<T>::getInstance(PacketCodec<T>& codec)
{
    static
    std::unordered_map
    <PacketCodec<T>*, PrefixedArrayPacketCodec<T>> codecInstances;

    static std::shared_mutex codecInstancesMutex;
    std::shared_lock lock(codecInstancesMutex);

    if (!codecInstances.contains(&codec))
    {
        // Yeah, could this be any worse...
        // unlocking and locking smart locks defeats the whole purpose

        lock.unlock();
        {
            std::unique_lock uniqueLock(codecInstancesMutex);

            codecInstances.insert(codec, PrefixedArrayPacketCodec());
        }
        lock.lock();
    }
    return *codecInstances.find(&codec);
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

// PUBLIC
