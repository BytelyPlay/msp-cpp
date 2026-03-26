module;
#include <mutex>
#include <shared_mutex>
#include <unordered_map>
#include <vector>

module ArrayPacketCodec;

// PUBLIC
template <typename T>
ArrayPacketCodec<T>& ArrayPacketCodec<T>::getInstance(Codec<T>& codec)
{
    static
    std::unordered_map
    <Codec<T>*, ArrayPacketCodec<T>> codecInstances;

    static std::shared_mutex codecInstancesMutex;
    std::shared_lock lock(codecInstancesMutex);

    if (!codecInstances.contains(&codec))
    {
        // Yeah, could this be any worse...
        // unlocking and locking smart locks defeats the whole purpose

        lock.unlock();
        {
            std::unique_lock uniqueLock(codecInstancesMutex);

            codecInstances.insert(codec, ArrayCodec());
        }
        lock.lock();
    }
    return *codecInstances.find(&codec);
}

template <typename T>
void ArrayPacketCodec<T>::serialize(const std::vector<T>& obj, TypedOutputStream& out)
{
    for (T& val : obj)
        codec.serialize(val, out);
}

template <typename T>
std::vector<T> ArrayPacketCodec<T>::deserialize(TypedInputStream& in)
{

}

// PRIVATE
template <typename T>
ArrayPacketCodec<T>::ArrayPacketCodec(Codec<T>& codec)
: codec(codec)
{
}

// PUBLIC
