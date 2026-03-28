module;

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

    void serialize(const int& obj, TypedOutputStream& out) override;
    int deserialize(TypedInputStream& in) override;
private:
    VarIntPacketCodec();
};