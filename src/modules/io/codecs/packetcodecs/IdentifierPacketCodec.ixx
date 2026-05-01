module;
#include <vector>

export module IdentifierPacketCodec;
import PacketCodec;
import TypedInputStream;
import TypedOutputStream;
import Identifier;

export class IdentifierPacketCodec : public PacketCodec<Identifier>
{
public:
    static IdentifierPacketCodec& getInstance();
public:
    using PacketCodec::serialize;
    using PacketCodec::deserialize;

    void serialize(const Identifier& obj, TypedOutputStream& out) override;
    Identifier deserialize(TypedInputStream& in) override;
private:
    IdentifierPacketCodec();
};