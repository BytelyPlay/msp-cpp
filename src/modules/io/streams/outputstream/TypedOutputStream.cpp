module;
#include <bit>
#include <algorithm>
#include <vector>

module TypedOutputStream;
import EndiannessUtils;

// PUBLIC
TypedOutputStream::TypedOutputStream()
= default;

// PUBLIC
void TypedOutputStream::writeBytes(const unsigned char* begin, const unsigned char* end)
{
    data.insert(
        data.end(),
        begin,
        end
    );
}

void TypedOutputStream::writeBytes(const std::vector<unsigned char>& bytes)
{
    data.insert(
        data.end(),
        bytes.begin(),
        bytes.end()
    );
}
// PUBLIC
void TypedOutputStream::writeByte(unsigned char byte)
{
    *this << byte;
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