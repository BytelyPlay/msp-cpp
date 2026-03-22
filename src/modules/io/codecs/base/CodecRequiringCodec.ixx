module;
#include <cstdint>
#include <sys/types.h>
#include <optional>
#include <vector>

export module CodecRequiringCodec;
import Codec;
import TypedInputStream;
import TypedOutputStream;

export template<typename T>
class CodecRequiringCodec
{
public:
    virtual void serialize(
        const T& obj,

        Codec<T>& codec,
        TypedOutputStream& out
    ) = 0;
    virtual T deserialize(
        TypedInputStream& in,
        Codec<T>& codec
    ) = 0;
public:
    std::vector<unsigned char> serialize(
        const T& obj,
        Codec<T>& codec
    );
    T deserialize(
        const std::vector<unsigned char>& data,
        Codec<T>& codec,

        uint& bytesConsumed
    );
public:
    virtual ~CodecRequiringCodec() = default;
};