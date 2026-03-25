module;
#include <mutex>
#include <shared_mutex>
#include <unordered_map>

module ArrayCodec;

// PUBLIC
template <typename T>
ArrayCodec<T>& ArrayCodec<T>::getInstance(Codec<T>& codec)
{
    static
    std::unordered_map
    <Codec<T>*, ArrayCodec<T>> codecInstances;

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
void ArrayCodec<T>::serialize(const std::vector<T>& obj, TypedOutputStream& out)
{
    for (T& val : obj)
        codec.serialize(val, out);
}

template <typename T>
std::vector<T> ArrayCodec<T>::deserialize(TypedInputStream& in)
{

}

// PRIVATE
template <typename T>
ArrayCodec<T>::ArrayCodec(Codec<T>& codec)
: codec(codec)
{
}

// PUBLIC
