module;
#include <string>

module GameProfilePacketCodec;
import UUIDPacketCodec;
import UUID;
import StringPacketCodec;
import PrefixedArrayPacketCodec;
import Property;
import PropertyPacketCodec;

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

    profile.uuid = uuidCodec.deserialize(in);
    profile.username = stringCodec.deserialize(in);
    profile.properties = prefixedArrayCodec.deserialize(in);

    return profile;
}
// PRIVATE
GameProfilePacketCodec::GameProfilePacketCodec()
{

}
