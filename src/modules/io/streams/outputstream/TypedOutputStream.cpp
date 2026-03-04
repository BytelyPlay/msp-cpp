module;
#include <bit>
#include <cstring>

module TypedOutputStream;
import EndiannessUtils;

// PUBLIC
TypedOutputStream::TypedOutputStream()
= default;

// PUBLIC
void TypedOutputStream::writeBytes(const unsigned char* begin, const unsigned char* end)
{
    std::copy(
        begin,
        end,
        data
    );
}

void TypedOutputStream::writeBytes(const std::vector<unsigned char>& bytes)
{
    std::copy(
        bytes.begin(),
        bytes.end(),
        data
    );
}

// PUBLIC
std::vector<unsigned char> TypedOutputStream::getData()
{
    return data;
}

// PUBLIC
void TypedOutputStream::operator<<(const std::vector<unsigned char>& bytes)
{
    writeBytes(bytes);
}

template <typename T>
void TypedOutputStream::operator<<(T num)
{
    static_assert(std::is_fundamental_v<T>);

    if (!EndiannessUtils::isBigEndian())
        num = std::byteswap(num);
    const auto bytes = reinterpret_cast<const unsigned char*>(&num);

    data.insert(data.end(),
        bytes,
        bytes + sizeof(T));
}