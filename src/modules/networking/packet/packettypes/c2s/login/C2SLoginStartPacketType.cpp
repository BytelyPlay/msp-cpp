module;
#include <memory>
#include <string>

module C2SLoginStartPacketType;
import C2SLoginStartPacket;
import StringPacketCodec;
import UUID;
import UUIDPacketCodec;
import S2CLoginFinishedPacket;
import GameProfile;
import MinecraftClient;
import MinecraftServer;
import MinecraftProtocol;
import Logger;

// PUBLIC
C2SLoginStartPacketType& C2SLoginStartPacketType::getInstance()
{
    static C2SLoginStartPacketType type;
    return type;
}

std::unique_ptr<PacketC2S> C2SLoginStartPacketType::deserialize(TypedInputStream& in)
{
    auto packet = std::make_unique<C2SLoginStartPacket>();

    StringPacketCodec& stringCodec = StringPacketCodec::getInstance();
    UUIDPacketCodec& uuidCodec = UUIDPacketCodec::getInstance();

    packet->username = stringCodec.deserialize(in);
    packet->uuid = uuidCodec.deserialize(in);

    return packet;
}
// PUBLIC
Phase C2SLoginStartPacketType::getPhase()
{
    return LOGIN;
}

int C2SLoginStartPacketType::getPacketID()
{
    return 0x00;
}

std::string C2SLoginStartPacketType::getPacketIdentifier()
{
    return "minecraft:hello";
}

// PRIVATE
C2SLoginStartPacketType::C2SLoginStartPacketType()
{
    this->setListener([](
        std::unique_ptr<PacketC2S> packet,
        MinecraftServer& server,
        MinecraftProtocol& protocol,
        MinecraftClient& client
    )
    {
        auto loginFinishedPacket = std::make_unique<S2CLoginFinishedPacket>();
        auto* loginStartPacket = static_cast<C2SLoginStartPacket*>(packet.get());

        client.setGameProfile(
            { loginStartPacket->username,
                loginStartPacket->uuid }
        );
        loginFinishedPacket->profile = client.getGameProfile();

        client.queue(std::move(loginFinishedPacket));
    });
}
// PUBLIC
