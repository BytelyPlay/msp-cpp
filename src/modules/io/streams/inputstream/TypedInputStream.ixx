module;
#include <vector>
#include <fstream>
#include <memory>

export module TypedInputStream;

export class TypedInputStream
{
public:
    /**
     * Constructs a TypedInputStream with 2 pointer representing the first and last byte.
     * @param begin First byte to operate on.
     * @param end Last byte to operate on.
     */
    TypedInputStream(const unsigned char* begin, const unsigned char* end);
public:
    std::vector<unsigned char> readBytes(size_t amount);
public:
    void operator>>(unsigned char& byte);
    void operator>>(unsigned char* byte);
private:
    const unsigned char *begin, *current, *end;
public:
    TypedInputStream operator=(const TypedInputStream&) = delete;
    TypedInputStream(const TypedInputStream&) = delete;
};