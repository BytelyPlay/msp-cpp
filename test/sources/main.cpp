#include <chrono>
#include <string>
#include <cstdint>
#include <thread>

import MinecraftProtocol;
import MinecraftServer;
import Logger;
import EndiannessUtils;
import TypedInputStream;
import TypedOutputStream;
import CustomMemoryArena;
import C2SIntentionPacketType;
import MinecraftClient;
import PacketC2S;
import C2SIntentionPacket;
import Base64Utils;
import UUID;
import UUIDPacketCodec;
import VarIntPacketCodec;
import C2SCustomPayloadPacketType;
import C2SFinishConfigurationPacketType;
import S2CFinishConfigurationPacket;
import Phase;
import S2CPlayerPositionPacketType;
import S2CPlayerPositionPacket;
import PacketS2C;

int main() {
    MinecraftProtocol protocol(4);
    protocol.init();
    C2SFinishConfigurationPacketType::getInstance().setListener([](
        std::unique_ptr<PacketC2S> packet,
        MinecraftServer& server,
        MinecraftProtocol& protocol,
        MinecraftClient& client
    )
    {
        client.setPhase(PLAY);
        std::unique_ptr<S2CPlayerPositionPacket> playerPosPacket =
            std::make_unique<S2CPlayerPositionPacket>();

        playerPosPacket->teleportId = 0;

        playerPosPacket->x = 0;
        playerPosPacket->y = 0;
        playerPosPacket->z = 0;

        playerPosPacket->velocityX = 100;
        playerPosPacket->velocityY = 0;
        playerPosPacket->velocityZ = 0;

        playerPosPacket->yaw = 0;
        playerPosPacket->pitch = 0;

        playerPosPacket->teleportFlags = 0;

        client.queue(std::move(playerPosPacket));
    });
    MinecraftServer server("127.0.0.1", 24213, protocol);
    protocol.awaitShutdown();
}
