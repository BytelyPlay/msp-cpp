module;

export module VarIntCodec;
import Codec;

import TypedInputStream;
import TypedOutputStream;

export class VarIntCodec : public Codec<int>
{
public:
    static VarIntCodec& getInstance();

    using Codec::deserialize;
    using Codec::serialize;

    void serialize(const int& obj, TypedOutputStream& out) override;
    int deserialize(TypedInputStream& in) override;
private:
    VarIntCodec();
public:
    VarIntCodec(const VarIntCodec&) = delete;
    VarIntCodec operator=(const VarIntCodec&) = delete;

    VarIntCodec(VarIntCodec&&) = delete;
    VarIntCodec operator=(VarIntCodec&&) = delete;
};