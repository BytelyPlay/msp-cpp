module;
#include <optional>
#include <vector>

export module ArrayPacketCodec;
import PacketCodec;
import TypedInputStream;
import TypedOutputStream;

// TODO: To be replaced with a FIXED array packet codec...
export template<typename T>
class ArrayPacketCodec : public PacketCodec<std::vector<T>>
{
public:
    static ArrayPacketCodec& getInstance(PacketCodec<T>& codec);

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
    ArrayPacketCodec(PacketCodec<T>& codec);
public:
    ArrayPacketCodec(const ArrayPacketCodec&) = delete;
    ArrayPacketCodec operator=(const ArrayPacketCodec&) = delete;

    ArrayPacketCodec(ArrayPacketCodec&&) = delete;
    ArrayPacketCodec operator=(ArrayPacketCodec&&) = delete;
};