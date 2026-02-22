module;
#include <vector>

export module Codec;

export template<typename T>
class Codec
{
public:
    virtual std::vector<unsigned char> serialize(
        const T& obj
    ) = 0;
    virtual T deserialize(
        const std::vector<unsigned char>& data
    ) = 0;
public:
    virtual ~Codec() = default;
};
