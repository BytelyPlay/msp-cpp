module;
#include <vector>
#include <fstream>

export module TypedInputStream;

export class TypedInputStream
{
public:
    TypedInputStream(std::vector<unsigned char> data);
    TypedInputStream(const std::vector<unsigned char>& data);
    TypedInputStream(const std::istream& in);
public:
    std::vector<unsigned char> readBytes(long long amount);
private:
    std::istream& in;
    std::vector<unsigned char> data_internal_;
};
