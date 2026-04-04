module;
#include <array>
#include <format>

export module UUID;
import RandUtils;
import Logger;

export struct UUID
{
    std::string toString();

    std::array<unsigned char, 16> uuid;
};
export UUID generateUUID();