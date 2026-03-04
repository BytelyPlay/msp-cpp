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
import TypedInputStream;

export template<typename T>
class PacketTypeC2S : public PacketType
{
    static_assert(__is_base_of(PacketC2S, T));
public:
    void setListener(std::function<void(T, MinecraftServer&, MinecraftProtocol&)> listener);

    void callListener(T packet,
        MinecraftServer& server,
        MinecraftProtocol& protocol);
public:
    int getPacketID() override = 0;
    std::string getPacketIdentifier() override = 0;

    bool isC2S() override;
public:
    T deserialize(std::vector<unsigned char> bytes, uint& bytesConsumed);
    virtual T deserialize(TypedInputStream& in) = 0;
private:
    std::function<
        void(T, MinecraftServer&, MinecraftProtocol&)
    > listener = std::function(
         [](T, MinecraftServer&, MinecraftProtocol&) {}
        );
};
