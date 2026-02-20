export module Packets;

// TODO: Read from a reports/packet.json and use the identifier to get the protocol ID.
export class Packets
{
public:
    static Packets& getInstance();
private:
    Packets();
public:
    Packets operator=(const Packets&) = delete;
    Packets(const Packets&) = delete;
};