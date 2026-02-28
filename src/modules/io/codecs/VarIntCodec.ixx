module;
#include <bitset>
#include <vector>

export module VarIntCodec;
import Codec;

import TypedInputStream;
import TypedOutputStream;

export class VarIntCodec : public Codec<int>
{
public:
    static const VarIntCodec CODEC;

    void serialize(const int& obj, TypedOutputStream& out) override;
    int deserialize(TypedInputStream& in) override;
};