module;
#include <vector>
#include <string>
#include <cstdint>

export module BasicCodec;

export template<typename T>
class BasicCodec
{
private:
    virtual std::vector<unsigned char> serialize(
        const T& obj
    ) = 0;
    virtual T deserialize(
        const std::vector<unsigned char>& data,
        uint& bytesConsumed
    ) = 0;
public:
    virtual ~BasicCodec() = default;
};