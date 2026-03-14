module;
#include <vector>
#include <string>

export module C2SIntentionPacket;
import PacketC2S;
import PacketType;

export class C2SIntentionPacket : public PacketC2S
{
public:
    enum Intent : int
    {
        STATUS = 1,
        LOGIN = 2,
        TRANSFER = 3
    };
public:
    PacketType& getPacketType() override;
public:
    int protocolVersion;
    std::string serverAddress;

    unsigned short serverPort;
    Intent intent;
};