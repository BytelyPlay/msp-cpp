module;
#include <vector>
#include <string>
#include <cstdint>

export module TypedOutputStream;
import EndiannessUtils;
import Concepts;

/**
 * An output stream with types,
 * everything should be serialized according to how minecraft does it.
 * That means most things are big endian.
 */
export class TypedOutputStream
{
public:
    TypedOutputStream();
public:
    void writeBytes(const unsigned char* begin,
        const unsigned char* end);
    void writeBytes(const std::vector<unsigned char>& bytes);
public:
    void writeByte(unsigned char byte);
public:
    std::vector<unsigned char> getData();
public:
    void operator<<(const std::vector<unsigned char>& bytes);

    template<Concepts::Fundamental T>
    void operator<<(T num);
private:
    std::vector<unsigned char> data;
public:
    TypedOutputStream operator=(const TypedOutputStream&) = delete;
    TypedOutputStream(const TypedOutputStream&) = delete;
};

// PUBLIC
// PUBLIC
// PUBLIC
// PUBLIC
template <Concepts::Fundamental T>
void TypedOutputStream::operator<<(T num)
{
    // This isn't one if, because the is floating point thing, has to be evaluated at compile-time.
    if constexpr (!std::is_floating_point_v<T>)
    {
        if (!EndiannessUtils::isBigEndian())
            num = std::byteswap(num);
    }

    const auto* bytes = reinterpret_cast<const unsigned char*>(&num);

    data.insert(
    data.end(),
        bytes,
        bytes + sizeof(T)
    );
}