module;
#include <sys/types.h>

export module VarIntPacketCodec;
import PacketCodec;

import TypedInputStream;
import TypedOutputStream;

export class VarIntPacketCodec : public PacketCodec<int>
{
private:
    static constexpr unsigned char SEGMENT_BITS = 0x7F; // 0111 1111
    static constexpr unsigned char CONTINUE_BIT = 0x80; // 1000 0000
public:
    static VarIntPacketCodec& getInstance();

    using PacketCodec::deserialize;
    using PacketCodec::serialize;

    void serialize(const int& obj, TypedOutputStream& out) override;
    int deserialize(TypedInputStream& in) override;
private:
    VarIntPacketCodec();
private:
    unsigned char getFirstByte(uint val);
};