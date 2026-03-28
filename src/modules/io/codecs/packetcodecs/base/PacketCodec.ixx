module;
#include <vector>
#include <string>
#include <cstdint>

export module PacketCodec;

import TypedInputStream;
import TypedOutputStream;

/* TODO: This codec needs to be more flexible
*/
export template<typename T>
class PacketCodec
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
    virtual ~PacketCodec() = default;
protected:
    PacketCodec() = default;
};

// PUBLIC
// PUBLIC
template <typename T>
std::vector<unsigned char> PacketCodec<T>::serialize(const T& obj)
{
    TypedOutputStream out;
    serialize(obj, out);
    return out.getData();
}

template <typename T>
T PacketCodec<T>::deserialize(const std::vector<unsigned char>& data, uint& bytesConsumed)
{
    TypedInputStream in(data.data(),
        data.data() + data.size());

    T val = deserialize(in);
    bytesConsumed = in.getBytesConsumed();

    return val;
}
