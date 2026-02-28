module;
#include <vector>

export module VarIntCodec;
import Codec;

import TypedInputStream;
import TypedOutputStream;

export class VarIntCodec : public Codec<int>
{
public:
    void serialize(const int& obj, TypedOutputStream& out) override;
    int deserialize(const TypedInputStream& in) override;
};
