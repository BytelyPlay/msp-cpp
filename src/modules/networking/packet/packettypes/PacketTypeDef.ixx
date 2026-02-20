module;
#include <string>
#include <vector>

export module PacketType:def;

import Packet;

export class PacketType
{
public:
    virtual std::string getPacketIdentifier() = 0;
    virtual int getPacketID() = 0;

    virtual void serialize(std::vector<unsigned char> bytes);
    virtual std::vector<unsigned char> deserialize(const Packet& p);
};
