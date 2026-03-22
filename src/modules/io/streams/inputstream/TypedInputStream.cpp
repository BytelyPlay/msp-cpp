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
    std::vector<unsigned char>& buffer,
    bool peek)
{
    ptrdiff_t dataLeft = this->end - this->current;

    if (amount > dataLeft)
        amount = dataLeft;

    if (buffer.size() < amount) buffer.resize(amount);

    memcpy(buffer.data(), this->current, amount);

    if (!peek) current += amount;

    return amount;
}

size_t TypedInputStream::readBytes(unsigned char* begin,
    unsigned char* end,
    bool peek)
{
    ptrdiff_t amount = end - begin;
    ptrdiff_t dataLeft = this->end - this->current;

    if (amount > dataLeft)
        amount = dataLeft;

    memcpy(begin, this->current, amount);

    if (!peek) current += amount;
    return amount;
}

unsigned char TypedInputStream::peek()
{
    return *current;
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
