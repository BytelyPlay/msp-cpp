module;
#include <sys/types.h>
#include <optional>

export module VarIntPacketCodec;
import PacketCodec;
import TypedInputStream;
import TypedOutputStream;

export class VarIntPacketCodec : public PacketCodec<int>
{
public:
    static VarIntPacketCodec& getInstance();

    using PacketCodec::deserialize;
    using PacketCodec::serialize;

    void serialize(const int& obj, TypedOutputStream& out, bool& successful) override;
    std::optional<int> deserialize(TypedInputStream& in) override;
private:
    VarIntPacketCodec();
private:
    unsigned char getFirstByte(uint val);
};