module;
#include <vector>

export module Packet;
import PacketType;

export class Packet
{
public:
    virtual PacketType& getPacketType() = 0;

    virtual std::vector<unsigned char> deserialize();
public:
    virtual ~Packet() = default;
};
