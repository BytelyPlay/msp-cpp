module;
#include <vector>
#include <fstream>
#include <memory>

export module TypedInputStream;

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
private:
    const unsigned char *begin, *current, *end;
public:
    TypedInputStream operator=(const TypedInputStream&) = delete;
    TypedInputStream(const TypedInputStream&) = delete;
};