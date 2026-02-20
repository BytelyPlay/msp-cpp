module;

module Packets;

// PUBLIC
Packets& Packets::getInstance()
{
    static Packets packets;
    return packets;
}
// PRIVATE
Packets::Packets() = default;
