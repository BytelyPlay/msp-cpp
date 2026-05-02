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

int main() {
    MinecraftProtocol protocol(4);
    protocol.init();
    MinecraftServer server("127.0.0.1", 24213, protocol);
    protocol.awaitShutdown();
}
