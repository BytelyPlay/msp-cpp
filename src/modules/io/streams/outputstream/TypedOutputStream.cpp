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
    std::copy(
        begin,
        end,
        data.end()
    );
}

void TypedOutputStream::writeBytes(const std::vector<unsigned char>& bytes)
{
    std::copy(
        bytes.begin(),
        bytes.end(),
        data.end()
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