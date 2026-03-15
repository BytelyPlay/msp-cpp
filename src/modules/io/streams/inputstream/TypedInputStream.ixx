module;
#include <vector>
#include <fstream>
#include <memory>

export module TypedInputStream;
import EndiannessUtils;

export class TypedInputStream
{
public:
    /**
     * Constructs a TypedInputStream with 2 pointers representing the first and last byte.
     * @param begin First byte to operate on.
     * @param end Last byte to operate on.
     */
    TypedInputStream(const unsigned char* begin, const unsigned char* end);
public:
    /**
     * Read an amount of bytes to a buffer from this stream.
     * @param amount Amount to Read
     * @param buffer Buffer to write to
     * @return How many bytes were read.
     */
    size_t readBytes(size_t amount,
                     std::vector<unsigned char>& buffer);

    uint getBytesConsumed();
    uint getBytesLeft();
public:
    /**
     * Read one byte
     * @param byte Reads one byte to a reference.
     * @return true if successful
     */
    bool operator>>(unsigned char& byte);
    /**
     * Read one byte
     * @param byte Reads one byte to a pointer.
     * @return true if successful
     */
    bool operator>>(unsigned char* byte);

    template<typename T>
    bool operator>>(T&);
private:
    const unsigned char *begin, *current, *end;
public:
    TypedInputStream operator=(const TypedInputStream&) = delete;
    TypedInputStream(const TypedInputStream&) = delete;
};

// PUBLIC
// PUBLIC
// PUBLIC
template <typename T>
bool TypedInputStream::operator>>(T& ref)
{
    static_assert(std::is_fundamental_v<T>);

    unsigned char bytes[sizeof(T)];
    for (int i = 0; i < sizeof(T); i++)
        if (!(*this >> bytes[i])) return false;

    T val = *(reinterpret_cast<T*>(bytes));
    if (!EndiannessUtils::isBigEndian())
        val = std::byteswap(val);

    ref = val;
    return true;
}

// PRIVATE
// PUBLIC
