module;
#include <optional>
#include <string>

module PropertyPacketCodec;
import StringPacketCodec;
import PrefixedOptionalPacketCodec;
import Logger;

// PUBLIC
PropertyPacketCodec& PropertyPacketCodec::getInstance()
{
    static PropertyPacketCodec codec;
    return codec;
}

void PropertyPacketCodec::serialize
(const Property& obj, TypedOutputStream& out, bool& successful)
{
    StringPacketCodec& stringCodec = StringPacketCodec::getInstance();
    auto& prefixedOptionalCodec =
        PrefixedOptionalPacketCodec<std::string>
    ::getInstance(stringCodec);

    stringCodec.serialize(obj.name, out, successful);
    if (!successful) return;
    stringCodec.serialize(obj.value, out, successful);
    if (!successful) return;
    prefixedOptionalCodec.serialize(obj.signature, out, successful);
}

std::optional<Property> PropertyPacketCodec::deserialize(TypedInputStream& in)
{
    StringPacketCodec& stringCodec = StringPacketCodec::getInstance();
    auto& prefixedOptionalCodec =
        PrefixedOptionalPacketCodec<std::string>
    ::getInstance(stringCodec);

    auto name = stringCodec.deserialize(in);
    auto key = stringCodec.deserialize(in);
    auto signature = prefixedOptionalCodec.deserialize(in);

    if (!name.has_value() || !key.has_value() || !signature.has_value())
    {
        Logger::warn("Unable to read property.");
        return {};
    }

    return {
        {
            name.value(),
            key.value(),
            signature.value()
        } };
}

// PRIVATE
PropertyPacketCodec::PropertyPacketCodec()
= default;
