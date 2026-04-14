module;
#include <functional>
#include <memory>
#include <vector>
#include <optional>

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
    void setListener(std::function<void(std::unique_ptr<PacketC2S>,
        MinecraftServer&,
        MinecraftProtocol&,
        MinecraftClient&)> listener);

    /**
     * Calls the listener of this packet type. Or doesn't if it doesn't exist.
     * @param packet The Packet
     * @param server The Server Object
     * @param protocol The Protocol Object
     * @param client The Client Object
     */
    void callListener(std::unique_ptr<PacketC2S> packet,
                      MinecraftServer& server,
                      MinecraftProtocol& protocol,
                      MinecraftClient& client);
    /**
     * Deserializes the packet and calls its listeners if it was able to deserialize it
     * @param in The input stream containing the packet.
     * @param server The server object.
     * @param protocol The protocol object.
     * @param client The client object.
     * @return True if it was successful, false otherwise. Would likely log if it wasn't successful.
     */
    bool deserializeAndCall(TypedInputStream& in,
                            MinecraftServer& server,
                            MinecraftProtocol& protocol,
                            MinecraftClient& client);
public:
    Phase getPhase() override = 0;
    int getPacketID() override = 0;

    std::string getPacketIdentifier() override = 0;

    bool isC2S() override;
public:
    std::unique_ptr<PacketC2S>
    deserialize(std::vector<unsigned char> bytes, uint& bytesConsumed);

    /**
     * Deserializes the packet.
     * @param in The input stream containing the packet.
     * @return An optional containing the packet if it was able to be parsed.
     */
    virtual std::optional<std::unique_ptr<PacketC2S>>
    deserialize(TypedInputStream& in) = 0;
private:
    // TODO: An option to make default listeners not get set.
    std::function<void(std::unique_ptr<PacketC2S>, MinecraftServer&,
        MinecraftProtocol&,
        MinecraftClient&)> listener =
        std::function<
            void(std::unique_ptr<PacketC2S>, MinecraftServer&,
                MinecraftProtocol&, MinecraftClient&)
    >(
         [](std::unique_ptr<PacketC2S>,
             MinecraftServer&,
             MinecraftProtocol&,
             MinecraftClient&) {}
        );
};