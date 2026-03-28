module;
#include <optional>
#include <string>

module PropertyPacketCodec;
import StringPacketCodec;
import PrefixedOptionalPacketCodec;

// PUBLIC
PropertyPacketCodec& PropertyPacketCodec::getInstance()
{
    static PropertyPacketCodec codec;
    return codec;
}

void PropertyPacketCodec::serialize
(const Property& obj, TypedOutputStream& out)
{
    StringPacketCodec& stringCodec = StringPacketCodec::getInstance();
    auto& prefixedOptionalCodec =
        PrefixedOptionalPacketCodec<std::string>
    ::getInstance(stringCodec);

    stringCodec.serialize(obj.name, out);
    stringCodec.serialize(obj.value, out);
    prefixedOptionalCodec.serialize(obj.signature, out);
}

Property PropertyPacketCodec::deserialize(TypedInputStream& in)
{
    StringPacketCodec& stringCodec = StringPacketCodec::getInstance();
    auto& prefixedOptionalCodec =
        PrefixedOptionalPacketCodec<std::string>
    ::getInstance(stringCodec);

    std::string name = stringCodec.deserialize(in);
    std::string key = stringCodec.deserialize(in);
    std::optional<std::string> signature = prefixedOptionalCodec.deserialize(in);

    return { name, key, signature };
}

// PRIVATE
PropertyPacketCodec::PropertyPacketCodec()
= default;
