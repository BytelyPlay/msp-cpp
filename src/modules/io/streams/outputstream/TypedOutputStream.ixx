module;
#include <vector>

export module TypedOutputStream;

export class TypedOutputStream
{
public:
    TypedOutputStream();
public:
    void writeBytes(const std::vector<unsigned char>& bytes);
public:
    std::vector<unsigned char> getData();
public:
    void operator<<(const std::vector<unsigned char>& bytes);

    void operator<<(const unsigned char& byte);
private:
    std::vector<unsigned char> data;
public:
    TypedOutputStream operator=(const TypedOutputStream&) = delete;
    TypedOutputStream(const TypedOutputStream&) = delete;
};