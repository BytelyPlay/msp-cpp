module;
#include <array>

export module UUID;

export struct UUID
{
    std::array<unsigned char, 16> uuid;
};
