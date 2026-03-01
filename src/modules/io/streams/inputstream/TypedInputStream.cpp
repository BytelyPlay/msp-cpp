module;
#include <cstring>
#include <fstream>

module TypedInputStream;
// PUBLIC
TypedInputStream::TypedInputStream(const unsigned char* begin, const unsigned char* end) :
begin(begin), current(begin), end(end)
{
}

// PUBLIC
size_t TypedInputStream::readBytes(size_t amount,
    std::vector<unsigned char>& buffer)
{
    ptrdiff_t diff = (current + amount) - end;
    amount = diff <= 0 ? amount : amount - diff;

    buffer.insert(
        buffer.end(),
        current,
        current + amount
    );

    current += amount;

    return amount;
}

uint TypedInputStream::getBytesConsumed()
{
    return current - begin;
}

uint TypedInputStream::getBytesLeft()
{
    return end - current;
}

// PUBLIC
bool TypedInputStream::operator>>(unsigned char& byte)
{
    if (current < end)
    {
        byte = *(current++);
        return true;
    }
    return false;
}

bool TypedInputStream::operator>>(unsigned char* byte)
{
    return this->
    operator>>(*byte);
}
