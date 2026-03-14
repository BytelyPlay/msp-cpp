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
import MinecraftClient;
import Phase;

export class PacketTypeC2S : public PacketType
{
public:
    void setListener(std::function<void(PacketC2S&, MinecraftServer&, MinecraftProtocol&, MinecraftClient&)> listener);

    /**
     * Calls the listener of this packet type. Or doesn't if it doesn't exist.
     * @param packet The Packet
     * @param server The Server Object
     * @param protocol The Protocol Object
     * @param client The Client Object
     */
    void callListener(PacketC2S& packet,
                      MinecraftServer& server,
                      MinecraftProtocol& protocol,
                      MinecraftClient& client);
    void deserializeAndCall(TypedInputStream& in,
                      MinecraftServer& server,
                      MinecraftProtocol& protocol,
                      MinecraftClient& client);
public:
    Phase getPhase() override = 0;
    int getPacketID() override = 0;

    std::string getPacketIdentifier() override = 0;

    bool isC2S() override;
public:
    PacketC2S&
    deserialize(std::vector<unsigned char> bytes, uint& bytesConsumed);

    /* TODO: Perhaps use a memory arena's
    memory for an std::shared_ptr
    instead of the heap, maybe use std::allocate_shared */
    virtual PacketC2S&
    deserialize(TypedInputStream& in) = 0;
private:
    std::function<void(PacketC2S&, MinecraftServer&,
        MinecraftProtocol&,
        MinecraftClient&)> listener =
        std::function<
            void(PacketC2S&, MinecraftServer&,
                MinecraftProtocol&, MinecraftClient&)
    >(
         [](PacketC2S&, MinecraftServer&, MinecraftProtocol&, MinecraftClient&) {}
        );
};