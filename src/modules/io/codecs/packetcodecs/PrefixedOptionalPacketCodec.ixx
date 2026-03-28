module;
#include <vector>
#include <string>
#include <cstdint>
#include <optional>

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
    PacketCodec<T>& codec;
};
