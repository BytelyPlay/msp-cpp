module;
#include <string>

export module MinecraftProtocol;

using string = std::string;

using uint = unsigned int;

using uint8 = unsigned char;
using uint16 = unsigned short;
using uint32 = unsigned int;
using uint64 = unsigned long;

export class MinecraftProtocol
{
public:
    MinecraftProtocol(string ip, uint16 port);
private:
};