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
    <Codec<T>*,
    ArrayCodec<T>> codecInstances;

    static std::shared_mutex codecInstancesMutex;
    std::shared_lock lock(codecInstancesMutex);

    if (!codecInstances.contains(&codec))
    {
        lock.release();
        std::unique_lock uniqueLock(codecInstancesMutex);

        codecInstances.insert(codec, ArrayCodec());

        uniqueLock.release();
        lock.lock();
    }
    return *codecInstances.find(&codec);
}

// PRIVATE
template <typename T>
ArrayCodec<T>::ArrayCodec(Codec<T>& codec)
: codec(codec)
{
}

// PUBLIC
