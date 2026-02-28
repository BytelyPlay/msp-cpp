module;
#include <string>
#include <vector>

export module Packets;
import PacketType;

// TODO: Read from a reports/packets.json and use the identifier to get the protocol ID.
export namespace Packets
{
    namespace S2C
    {

    }
    namespace C2S
    {
        void receivedPacket(std::vector<unsigned char> data);
    }
    void registerPacket(int id, std::string identifier, PacketType& type);
}