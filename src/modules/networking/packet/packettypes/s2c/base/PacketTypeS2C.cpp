module;
#include <vector>
#include <memory>

module PacketTypeS2C;

// PUBLIC
std::vector<unsigned char> PacketTypeS2C::serialize(
    std::unique_ptr<PacketS2C> packet, bool& success)
{
    TypedOutputStream out;
    serialize(std::move(packet), out, success);
    return out.getData();
}

// PUBLIC
bool PacketTypeS2C::isC2S()
{
    return false;
}
