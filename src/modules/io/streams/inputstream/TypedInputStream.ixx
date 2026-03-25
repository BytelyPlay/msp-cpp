module;
#include <vector>
#include <fstream>
#include <memory>

export module TypedInputStream;
import EndiannessUtils;
import Concepts;
import Logger;

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
     * Will overwrite any data in the buffer.
     * @param amount Amount to Read
     * @param buffer Buffer to write to
     * @param peek Should peek, if true the current pointer won't advance. Defaults to false
     * @return How many bytes were read.
     */
    size_t readBytes(size_t amount,
                     std::vector<unsigned char>& buffer,
                     bool peek = false);
    /**
     * @param begin First Byte to read into
     * @param end Last byte to read into
     * @param peek Should peek, if true the current pointer won't advance. Defaults to false
     * @return Amount of bytes read
     */
    size_t readBytes(unsigned char* begin,
                     unsigned char* end,
                     bool peek= false);
    /**
     * Peeks, reads the next byte without forwarding the pointer.
     * @return What the next byte would be, if you read.
     */
    unsigned char peek();

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

    template<Concepts::Fundamental T>
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
template <Concepts::Fundamental T>
bool TypedInputStream::operator>>(T& ref)
{
    unsigned char bytes[sizeof(T)];
    for (int i = 0; i < sizeof(T); i++)
        if (!(*this >> bytes[i])) return false;

    T val = *(reinterpret_cast<T*>(bytes));
    if (!EndiannessUtils::isBigEndian() && !std::is_floating_point_v<T>)
        val = std::byteswap(val);

    ref = val;
    return true;
}

// PRIVATE
// PUBLIC
