module;
#include <array>

export module UUID;

export struct UUID
{
    std::array<std::byte, 16> uuid;
};
