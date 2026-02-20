module;
#include <vector>

export module PacketTypeS2C;
import PacketType;
import PacketS2C;

export template<typename T>
class PacketTypeS2C : public PacketType
{
    static_assert(__is_base_of(PacketS2C, T));

};
