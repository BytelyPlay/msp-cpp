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
std::vector<unsigned char> TypedInputStream::readBytes(size_t amount)
{
    std::vector<unsigned char> bytes =
        std::vector<unsigned char>();

    ptrdiff_t diff = (current + amount) - end;
    amount = diff <= 0 ? amount : amount - diff;

    bytes.resize(amount);
    memcpy(bytes.data(), current, amount);

    current += amount;

    return bytes;
}
// PUBLIC
void TypedInputStream::operator>>(unsigned char& byte)
{
    if (current < end)
    {
        byte = *(current++);
    }
}

void TypedInputStream::operator>>(unsigned char* byte)
{
    this->
    operator>>(*byte);
}
