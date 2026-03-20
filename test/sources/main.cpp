#include <chrono>
#include <string>
#include <cstdint>

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

int main() {
    Logger::debug("Is Big Endian: " +
        std::string((EndiannessUtils::isBigEndian() ? "Yes" : "No")));

    TypedOutputStream out;
    out << 1234567;

    MinecraftProtocol protocol(4);
    protocol.init();
    MinecraftServer server("127.0.0.1", 24213, protocol);
    protocol.awaitShutdown();
}
