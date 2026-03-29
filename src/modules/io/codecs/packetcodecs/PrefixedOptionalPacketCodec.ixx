module;
#include <vector>
#include <string>
#include <cstdint>
#include <optional>
#include <unordered_map>
#include <shared_mutex>
#include <mutex>

export module PrefixedOptionalPacketCodec;
import PacketCodec;
import TypedInputStream;
import TypedOutputStream;

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
    std::vector<unsigned char> serialize(
        const std::optional<T>& opt,
        PacketCodec<T>& codec
    );
    T deserialize(
        const std::vector<unsigned char>& data,
        PacketCodec<T>& codec,

        uint& bytesConsumed
    );
private:
    PrefixedOptionalPacketCodec(PacketCodec<T> codec);
private:
    const PacketCodec<T>& codec;
};
// PUBLIC
template <typename T>
PrefixedOptionalPacketCodec<T>&
    PrefixedOptionalPacketCodec<T>::getInstance(PacketCodec<T>& codec)
{
    // TODO: Don't duplicate code...
    static
    std::unordered_map
    <PacketCodec<T>*, PrefixedOptionalPacketCodec> codecInstances;

    static std::shared_mutex codecInstancesMutex;
    std::shared_lock lock(codecInstancesMutex);

    if (!codecInstances.contains(&codec))
    {
        // Yeah, could this be any worse...
        // unlocking and locking smart locks defeats the whole purpose

        lock.unlock();
        {
            std::unique_lock uniqueLock(codecInstancesMutex);

            codecInstances.insert(codec, PrefixedOptionalPacketCodec(codec));
        }
        lock.lock();
    }
    return *codecInstances.find(&codec);
}
// PUBLIC
// PRIVATE
// PRIVATE