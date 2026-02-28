module;
#include <vector>

export module Codec;
import TypedInputStream;
import TypedOutputStream;

import BasicCodec;

export template<typename T>
class Codec : public BasicCodec<T>
{
public:
    virtual void serialize(
        const T& obj,
        TypedOutputStream& out
    ) = 0;
    virtual T deserialize(
        const TypedInputStream& in
    ) = 0;
public:
    std::vector<unsigned char> serialize(
        const T& obj
    ) override;
    T deserialize(
        const std::vector<unsigned char>& data
    ) override;
public:
    virtual ~Codec() = default;
};
