module;
#include <optional>
#include <vector>

export module PrefixedArrayPacketCodec;
import PacketCodec;
import TypedInputStream;
import TypedOutputStream;

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