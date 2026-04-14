module;
#include <cstring>
#include <fstream>

module TypedInputStream;

// PUBLIC
TypedInputStream::TypedInputStream(const unsigned char* begin, const unsigned char* end) :
begin(begin), next(begin), end(end)
{
}

// PUBLIC
size_t TypedInputStream::readBytes(size_t amount,
    std::vector<unsigned char>& buffer,
    bool peek)
{
    ptrdiff_t dataLeft = this->end - this->next;

    if (amount > dataLeft)
        amount = dataLeft;

    if (buffer.size() < amount) buffer.resize(amount);

    memcpy(buffer.data(), this->next, amount);

    if (!peek) next += amount;

    return amount;
}

size_t TypedInputStream::readBytes(unsigned char* begin,
    unsigned char* end,
    bool peek)
{
    ptrdiff_t amount = end - begin;
    ptrdiff_t dataLeft = this->end - this->next;

    if (amount > dataLeft)
        amount = dataLeft;

    memcpy(begin, this->next, amount);

    if (!peek) next += amount;
    return amount;
}

unsigned char TypedInputStream::peek()
{
    return *next;
}

uint TypedInputStream::getBytesConsumed()
{
    return next - begin;
}

uint TypedInputStream::getBytesLeft()
{
    return end - next;
}

// PUBLIC
bool TypedInputStream::operator>>(unsigned char& byte)
{
    if (next < end)
    {
        byte = *(next++);
        return true;
    }
    return false;
}

bool TypedInputStream::operator>>(unsigned char* byte)
{
    return this->
    operator>>(*byte);
}
