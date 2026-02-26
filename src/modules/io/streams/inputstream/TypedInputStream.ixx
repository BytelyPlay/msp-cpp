module;
#include <vector>
#include <fstream>
#include <memory>

export module TypedInputStream;
import FlexibleStreamBuf;

export class TypedInputStream
{
public:
    TypedInputStream(std::vector<unsigned char> data);
public:
    std::vector<unsigned char> readBytes(long long amount);
private:
    std::basic_istream<unsigned char> in;

    /* TODO: I cannot stress enough about how bad it is to make 2 heap allocations on construction
    for something that is supposed to construct quickly.*/
    std::vector<unsigned char> dataInternal_;

    std::unique_ptr<std::basic_streambuf<unsigned char>> streambufInternal_;
};
