#include <string>

import MinecraftProtocol;
import MinecraftServer;
import Logger;
import EndiannessUtils;

int main() {
    Logger::debug("Is Big Endian: " +
        std::string((EndiannessUtils::isBigEndian() ? "Yes" : "No")));
    
    MinecraftProtocol protocol(4);
    protocol.init();
    MinecraftServer server("127.0.0.1", 24213, protocol);
    protocol.awaitShutdown();
}
