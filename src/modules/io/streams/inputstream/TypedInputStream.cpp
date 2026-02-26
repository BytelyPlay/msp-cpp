module;
#include <algorithm>
#include <fstream>

module TypedInputStream;

// PUBLIC
TypedInputStream::TypedInputStream(std::vector<unsigned char> data)
{
    in = std::basic_istream<unsigned char>(data);
    std::<unsigned char> buf;

}

TypedInputStream::TypedInputStream(const std::vector<unsigned char>& data)
{
}

TypedInputStream::TypedInputStream(const std::istream& in)
{

}
// PUBLIC
std::vector<unsigned char> TypedInputStream::readBytes(long long amount)
{

}
