module;
#include <sys/types.h>

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
    int deserialize(TypedInputStream& in, bool& successful) override;
private:
    VarIntPacketCodec();
private:
    unsigned char getFirstByte(uint val);
};