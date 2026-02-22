module;
#include <string>

module EndiannessUtils;
import Logger;
#include "Types.hpp"

bool isBigEndianInternal()
{
    uint16 i = 1;
    auto* bytes = reinterpret_cast<
        unsigned char*
    >(&i);

    // Big Endian
    // 0000 0000 0000 0001

    // Little Endian
    // 1000 0000 0000 0000

    if (bytes[0] > 0) return false;
    return true;
}

bool EndiannessUtils::isBigEndian()
{
    static bool isBigEndian = isBigEndianInternal();
    return isBigEndian;
}