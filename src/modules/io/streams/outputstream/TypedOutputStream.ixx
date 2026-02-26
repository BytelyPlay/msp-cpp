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
    std::ostream& out;

    std::vector<unsigned char>& data; // This is the one to use.
    std::vector<unsigned char> data_internal; // This is the internal one in case we have to own the vector.
};