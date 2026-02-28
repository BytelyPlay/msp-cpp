module;
#include <string>

module Packets;
import VarIntCodec;

// NAMESPACE Packets::C2S
void Packets::C2S::receivedPacket(std::vector<unsigned char> data)
{

}
// NAMESPACE Packets
// TODO: Only the identifier should be needed, the id gets taken from reports/packets.json
void Packets::registerPacket(int id, std::string identifier, PacketType& type)
{

}
