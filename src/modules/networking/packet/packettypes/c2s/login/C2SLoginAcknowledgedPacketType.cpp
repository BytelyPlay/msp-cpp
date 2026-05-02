module;
#include <string>
#include <memory>


module C2SLoginAcknowledgedPacketType;
import VarIntPacketCodec;
import MinecraftClient;
import MinecraftProtocol;
import MinecraftServer;
import PacketParsingException;
import TypedInputStream;
import Phase;
import PacketC2S;
import C2SLoginAcknowledgedPacket;
import S2CFinishConfigurationPacket;

// PUBLIC
C2SLoginAcknowledgedPacketType& C2SLoginAcknowledgedPacketType::getInstance()
{
    static C2SLoginAcknowledgedPacketType type;
    return type;
}

// PUBLIC
Phase C2SLoginAcknowledgedPacketType::getPhase()
{
    return LOGIN;
}

int C2SLoginAcknowledgedPacketType::getPacketID()
{
    return 3;
}

std::string C2SLoginAcknowledgedPacketType::getPacketIdentifier()
{
    return "minecraft:login_acknowledged";
}

// PUBLIC
std::unique_ptr<PacketC2S> C2SLoginAcknowledgedPacketType::deserialize(TypedInputStream& in)
{
    std::unique_ptr<C2SLoginAcknowledgedPacket> packet =
        std::make_unique<C2SLoginAcknowledgedPacket>();
    return packet;
}
// PRIVATE
C2SLoginAcknowledgedPacketType::C2SLoginAcknowledgedPacketType()
{
    this->setListener([](
     std::unique_ptr<PacketC2S> packet,
     MinecraftServer& server,
     MinecraftProtocol& protocol,
     MinecraftClient& client
   )
   {
        client.setPhase(CONFIGURATION);
        client.queue(std::make_unique<S2CFinishConfigurationPacket>());
   });
}