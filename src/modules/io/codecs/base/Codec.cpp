module;
#include <vector>
#include <sys/types.h>
#include <cstdint>

module Codec;

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
    bytesConsumed = in.getBytesConsumed();

    return deserialize(in);
}
