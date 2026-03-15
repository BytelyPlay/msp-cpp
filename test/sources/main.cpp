#include <string>
#include <cstdint>

import MinecraftProtocol;
import MinecraftServer;
import Logger;
import EndiannessUtils;
import TypedInputStream;
import TypedOutputStream;
import CustomMemoryArena;
int main() {
    CustomMemoryArena arena(1024 * 1024);
    void* mem = arena.alloc(1024, 32);

    auto* memAsBytes = reinterpret_cast<unsigned char*>(mem);
    memAsBytes[1024] = 59;
    Logger::debug(std::to_string(memAsBytes[1024]));

    return 0;

    Logger::debug("Is Big Endian: " +
        std::string((EndiannessUtils::isBigEndian() ? "Yes" : "No")));

    TypedOutputStream out;
    out << 1234567;

    MinecraftProtocol protocol(4);
    protocol.init();
    MinecraftServer server("127.0.0.1", 24213, protocol);
    protocol.awaitShutdown();
}
