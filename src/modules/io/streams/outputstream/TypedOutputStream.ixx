module;
#include <vector>
#include <string>

export module TypedOutputStream;
#include "Types.hpp"

/**
 * An output stream with types,
 * everything should be serialized according to how minecraft does it.
 * That means most things are big endian.
 */
export class TypedOutputStream
{
public:
    TypedOutputStream();
public:
    void writeBytes(const unsigned char* begin,
        const unsigned char* end);
    void writeBytes(const std::vector<unsigned char>& bytes);
public:
    std::vector<unsigned char> getData();
public:
    void operator<<(const std::vector<unsigned char>& bytes);

    template<typename T>
    void operator<<(T num);
private:
    std::vector<unsigned char> data;
public:
    TypedOutputStream operator=(const TypedOutputStream&) = delete;
    TypedOutputStream(const TypedOutputStream&) = delete;
};