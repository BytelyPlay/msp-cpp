module;
#include <vector>

export module VarIntCodec;
import Codec;

export class VarIntCodec : public Codec<int>
{
    std::vector<unsigned char> serialize(
        const int& obj
    ) override;
    int deserialize(
        const std::vector<unsigned char>& data
    ) override;
};
