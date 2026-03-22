module;
#include <array>
#include <bitset>
#include <cstring>
#include <vector>

export module UUID;
import RandUtils;

export struct UUID
{
    std::array<unsigned char, 16> uuid;
};
export UUID generateUUID()
{
    std::array<unsigned char, 16> bytes = {};

    RandUtils::randBytes(16, bytes.data());

    // time_hi_and_version
    bytes[6] |= 0x40;
    bytes[6] &= 0x4F;

    // clock_seq_hi_and_reserved
    bytes[8] |= 0x80;
    bytes[8] &= 0x8F;

    return { bytes };
}