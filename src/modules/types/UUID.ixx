module;
#include <array>
#include <bitset>
#include <cstring>
#include <vector>
#include <format>

export module UUID;
import RandUtils;
import Logger;

export struct UUID
{
    std::string toString()
    {
        std::string hex;
        for (unsigned char& newByte : uuid)
            hex += std::format("{:02x}", newByte);
        Logger::debug(hex);

        return hex.substr(0, 8) + "-" +
            hex.substr(8, 4) + "-" +
                hex.substr(12, 4) + "-" +
                    hex.substr(16, 4) + "-" +
                        hex.substr(20, 12);
    }
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