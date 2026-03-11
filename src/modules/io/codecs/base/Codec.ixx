module;
#include <vector>
#include <string>
#include <cstdint>

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
        TypedInputStream& in
    ) = 0;
public:
    std::vector<unsigned char> serialize(
        const T& obj
    ) override;
    T deserialize(
        const std::vector<unsigned char>& data,
        uint& bytesConsumed
    ) override;
public:
    virtual ~Codec() = default;
};

// PUBLIC
// PUBLIC
template <typename T>
std::vector<unsigned char> Codec<T>::serialize(const T& obj)
{
    TypedOutputStream out;
    serialize(obj, out);
    return out.getData();
}

template <typename T>
T Codec<T>::deserialize(const std::vector<unsigned char>& data, uint& bytesConsumed)
{
    TypedInputStream in(data.data(),
        data.data() + data.size());

    T val = deserialize(in);
    bytesConsumed = in.getBytesConsumed();

    return val;
}
