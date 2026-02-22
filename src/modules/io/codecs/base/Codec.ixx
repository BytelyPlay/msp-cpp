module;
#include <vector>

export module Codec;
import TypedInputStream;
import TypedOutputStream;

export template<typename T>
class Codec
{
public:
    virtual void serialize(
        const T& obj,
        TypedOutputStream& out
    ) = 0;
    virtual T deserialize(
        const TypedInputStream& in
    ) = 0;

    virtual std::vector<unsigned char> serialize(
        const T& obj
    );
    virtual T deserialize(
        const std::vector<unsigned char>& data
    );
public:
    virtual ~Codec() = default;
};
