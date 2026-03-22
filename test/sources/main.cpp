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
import UUID;

int main() {
    Logger::debug("Is Big Endian: " +
        std::string((EndiannessUtils::isBigEndian() ? "Yes" : "No")));

    UUID uuid = generateUUID();

    std::string hexBytes;
    for (unsigned char& newByte : uuid.uuid)
    {
        hexBytes += std::format("{:02X} ", newByte);
    }
    Logger::debug(hexBytes + "         " + uuid.toString());

    TypedOutputStream out;
    out << 1234567;

    MinecraftProtocol protocol(4);
    protocol.init();
    MinecraftServer server("127.0.0.1", 24213, protocol);
    protocol.awaitShutdown();
}
