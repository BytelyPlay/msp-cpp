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

int main() {
    VarIntPacketCodec& varIntCodec = VarIntPacketCodec::getInstance();

    for (int i = 0; i < 1000; i++)
    {
        uint consumed;

        std::vector<unsigned char> varInt = varIntCodec.serialize(i);
        if (varIntCodec.deserialize(varInt, consumed) != i)
            Logger::warn(
                std::format(
                    "VarIntPacketCodec has something wrong with it: "
                    "{} produced: {}", i,
                    varIntCodec.deserialize(varInt, consumed)
                    ));
    }
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
