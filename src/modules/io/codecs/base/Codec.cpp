module;
#include <vector>
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
T Codec<T>::deserialize(const std::vector<unsigned char>& data)
{
    TypedInputStream in(data.data(),
        data.data() + data.size());
    return deserialize(in);
}
// PROTECTED
template <typename T>
Codec<T>::Codec()
= default;
