module;
#include <optional>
#include <vector>

export module FixedArrayPacketCodec;
import PacketCodec;
import TypedInputStream;
import TypedOutputStream;

// TODO: To be replaced with a FIXED array packet codec...
export template<typename T>
class FixedArrayPacketCodec : public PacketCodec<std::vector<T>>
{
public:
    static FixedArrayPacketCodec& getInstance(PacketCodec<T>& codec);

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
    FixedArrayPacketCodec(PacketCodec<T>& codec);
public:
    FixedArrayPacketCodec(const FixedArrayPacketCodec&) = delete;
    FixedArrayPacketCodec operator=(const FixedArrayPacketCodec&) = delete;

    FixedArrayPacketCodec(FixedArrayPacketCodec&&) = delete;
    FixedArrayPacketCodec operator=(FixedArrayPacketCodec&&) = delete;
};