module;
#include <vector>
#include <string>
#include <cstdint>

export module PacketCodec;

import TypedInputStream;
import TypedOutputStream;

/* TODO: This is the stupidest thing yet, Codecs aren't really made for networking. I have
written a lot of non-flexible stuff so I'll just have to fill in the gaps for now...
But when we get to NBT and whatnot I will have to split up Codecs and Packet serialization.
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
