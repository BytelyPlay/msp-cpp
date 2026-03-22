module;
#include <vector>
#include <string>
#include <cstdint>

export module Codec;
import TypedInputStream;
import TypedOutputStream;

// TODO: To be honest, the only thing the codec system is lacking is a MapCodec
export template<typename T>
class Codec
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
    );
    T deserialize(
        const std::vector<unsigned char>& data,
        uint& bytesConsumed
    );
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
