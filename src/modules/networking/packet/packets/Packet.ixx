module;
#include <vector>

export module Packet;
import PacketType;

export class Packet
{
public:
    virtual PacketType& getPacketType() = 0;
public:
    virtual ~Packet() = default;
};
