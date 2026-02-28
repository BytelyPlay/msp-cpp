module;
#include <fstream>
#include <vector>

export module TypedOutputStream;

export class TypedOutputStream
{
public:
    TypedOutputStream();

    TypedOutputStream(std::vector<unsigned char>& toFill);
    TypedOutputStream(std::ostream& out);
public:
    void writeBytes(std::vector<unsigned char>& bytes);
public:
    std::vector<unsigned char>& getData();
private:

public:
    TypedOutputStream operator=(const TypedOutputStream&) = delete;
    TypedOutputStream(const TypedOutputStream&) = delete;
};