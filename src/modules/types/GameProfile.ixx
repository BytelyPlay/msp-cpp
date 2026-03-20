module;
#include <string>

export module GameProfile;
import UUID;

export struct GameProfile
{
    std::string username;
    UUID uuid;


};
