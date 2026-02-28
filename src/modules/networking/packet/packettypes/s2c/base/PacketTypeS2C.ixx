module;
#include <vector>
#include <memory>

export module PacketTypeS2C;
import PacketType;
import PacketS2C;
import Packet;

export template<typename T>
class PacketTypeS2C : public PacketType
{
    static_assert(__is_base_of(PacketS2C, T));
public:
    virtual std::shared_ptr<Packet> serialize(
        const std::vector<unsigned char>& data
    ) = 0;
};
