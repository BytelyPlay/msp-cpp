module;
#include <vector>
#include <string>
#include <optional>
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
    virtual std::optional<T> deserialize(
        TypedInputStream& in
    ) = 0;
public:
    std::vector<unsigned char> serialize(
        const T& obj,
        bool& successful
    );
    std::optional<T> deserialize(
        const std::vector<unsigned char>& data,
        uint& bytesConsumed
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
std::optional<T> PacketCodec<T>::deserialize(const std::vector<unsigned char>& data,
    uint& bytesConsumed)
{
    TypedInputStream in(data.data(),
        data.data() + data.size());

    std::optional<T> optionalVal = deserialize(in);
    bytesConsumed = in.getBytesConsumed();

    return optionalVal;
}
