module;
#include <vector>
#include <fstream>

export module TypedInputStream;

export class TypedInputStream
{
public:
    TypedInputStream(const std::vector<unsigned char>& data);
    TypedInputStream(const std::istream& in);
public:

};
