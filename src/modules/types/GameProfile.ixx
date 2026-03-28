module;
#include <string>
#include <vector>

export module GameProfile;
import UUID;
import Property;
import PacketCodec;

export struct GameProfile
{
    std::string username;
    UUID uuid;

    std::vector<Property> properties;
};