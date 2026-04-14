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
        TypedOutputStream& out,
        bool& successful
    ) = 0;
    virtual T deserialize(
        TypedInputStream& in,
        bool& successful
    ) = 0;
public:
    std::vector<unsigned char> serialize(
        const T& obj,
        bool& successful
    );
    T deserialize(
        const std::vector<unsigned char>& data,
        uint& bytesConsumed,
        bool& successful
    );
public:
    virtual ~PacketCodec() = default;
protected:
    PacketCodec() = default;
public:
    PacketCodec(const PacketCodec&) = delete;
    PacketCodec& operator=(const PacketCodec&) = delete;

    PacketCodec(PacketCodec&&) = delete;
    PacketCodec& operator=(PacketCodec&&) = delete;
};

// PUBLIC
// PUBLIC
template <typename T>
std::vector<unsigned char> PacketCodec<T>::serialize(const T& obj, bool& successful)
{
    TypedOutputStream out;
    serialize(obj, out, successful);
    return out.getData();
}

template <typename T>
T PacketCodec<T>::deserialize(const std::vector<unsigned char>& data,
    uint& bytesConsumed, bool& successful)
{
    TypedInputStream in(data.data(),
        data.data() + data.size());

    T val = deserialize(in, successful);
    bytesConsumed = in.getBytesConsumed();

    return val;
}
