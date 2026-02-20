module;
#include <string>
#include <vector>

export module PacketType;

export class PacketType
{
public:
    virtual std::string getPacketIdentifier() = 0;
    virtual int getPacketID() = 0;
public:
    virtual ~PacketType() = default;
};
