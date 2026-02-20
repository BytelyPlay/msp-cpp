module;
#include <functional>
#include <memory>
#include <vector>

export module PacketTypeC2S;
import PacketType;
import Packet;
import PacketC2S;
import MinecraftServer;
import MinecraftProtocol;

export template<typename T>
class PacketTypeC2S : public PacketType
{
    static_assert(__is_base_of(PacketC2S, T));
public:
    virtual std::shared_ptr<Packet> serialize(
        const std::vector<unsigned char>& data
    ) = 0;
public:
    void setListener(std::function<void(T, MinecraftServer&, MinecraftProtocol&)> listener);
private:
    std::function<void(T, MinecraftServer&, MinecraftProtocol&)> listener;
};
