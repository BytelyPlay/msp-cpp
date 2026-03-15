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

int main() {
    Logger::debug("Is Big Endian: " +
        std::string((EndiannessUtils::isBigEndian() ? "Yes" : "No")));

    TypedOutputStream out;
    out << 1234567;

    MinecraftProtocol protocol(4);
    protocol.init();
    C2SIntentionPacketType::getInstance().setListener([](
        std::unique_ptr<PacketC2S> basePacket,
        MinecraftServer&,
        MinecraftProtocol&,
        MinecraftClient&)
    {
        auto* packet = static_cast<C2SIntentionPacket*>(basePacket.get());

        Logger::debug("hi " + std::to_string(packet->intent) + " " + packet->serverAddress + " " + std::to_string(packet->serverPort));
    });
    MinecraftServer server("127.0.0.1", 24213, protocol);
    protocol.awaitShutdown();
}
