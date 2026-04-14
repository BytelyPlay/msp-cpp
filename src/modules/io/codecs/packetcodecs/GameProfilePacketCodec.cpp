module;
#include <string>
#include <optional>

module GameProfilePacketCodec;
import UUIDPacketCodec;
import UUID;
import StringPacketCodec;
import PrefixedArrayPacketCodec;
import Property;
import PropertyPacketCodec;
import Logger;

// PUBLIC
GameProfilePacketCodec& GameProfilePacketCodec::getInstance()
{
    static GameProfilePacketCodec codec;
    return codec;
}

void GameProfilePacketCodec::serialize(const GameProfile& obj,
                                       TypedOutputStream& out, bool& successful)
{
    auto& uuidCodec = UUIDPacketCodec::getInstance();
    auto& stringCodec = StringPacketCodec::getInstance();
    auto& propertyCodec = PropertyPacketCodec::getInstance();
    auto& prefixedArrayCodec =
        PrefixedArrayPacketCodec<Property>
    ::getInstance(propertyCodec);

    uuidCodec.serialize(obj.uuid, out, successful);
    if (!successful) return;
    stringCodec.serialize(obj.username, out, successful);
    if (!successful) return;
    prefixedArrayCodec.serialize(obj.properties, out, successful);
}

std::optional<GameProfile> GameProfilePacketCodec::deserialize(TypedInputStream& in)
{
    GameProfile profile;

    auto& uuidCodec = UUIDPacketCodec::getInstance();
    auto& stringCodec = StringPacketCodec::getInstance();
    auto& propertyCodec = PropertyPacketCodec::getInstance();
    auto& prefixedArrayCodec =
        PrefixedArrayPacketCodec<Property>
    ::getInstance(propertyCodec);

    auto optUUID = uuidCodec.deserialize(in);
    auto optUsername = stringCodec.deserialize(in);
    auto optProperties = prefixedArrayCodec.deserialize(in);

    if (!optUUID.has_value() ||
        !optUsername.has_value() ||
        !optProperties.has_value())
    {
        Logger::warn("Couldn't deserialize something in GameProfile.");
        return {};
    }
    profile.uuid = optUUID.value();
    profile.username = optUsername.value();
    profile.properties = optProperties.value();

    return profile;
}
// PRIVATE
GameProfilePacketCodec::GameProfilePacketCodec()
{

}
