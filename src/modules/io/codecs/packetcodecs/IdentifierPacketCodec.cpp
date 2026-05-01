module;
#include <string>

module IdentifierPacketCodec;
import StringPacketCodec;

// PUBLIC
IdentifierPacketCodec& IdentifierPacketCodec::getInstance()
{
    static IdentifierPacketCodec codec;
    return codec;
}
// PUBLIC
void IdentifierPacketCodec::serialize(const Identifier& obj,
    TypedOutputStream& out)
{
    StringPacketCodec& stringCodec = StringPacketCodec::getInstance();

    stringCodec.serialize(
        obj.identifierNameSpace
        + ":" + obj.identifierValue,
        out
    );
}

Identifier IdentifierPacketCodec::deserialize(TypedInputStream& in)
{
    StringPacketCodec& stringCodec = StringPacketCodec::getInstance();
    Identifier id;

    std::string identifier = stringCodec.deserialize(in);
    size_t posOfColon = identifier.find_first_of(':');

    id.identifierNameSpace = identifier.substr(0, posOfColon);
    id.identifierValue = identifier.substr(posOfColon);

    return id;
}

// PRIVATE
IdentifierPacketCodec::IdentifierPacketCodec()
= default;