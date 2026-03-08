module;
#include <string>
#include <cstdint>

module VarIntCodec;
import EndiannessUtils;
import Logger;
import CodecParsingException;

// PUBLIC
VarIntCodec VarIntCodec::CODEC = VarIntCodec();

void VarIntCodec::serialize(const int& valRef, TypedOutputStream& out)
{
    // This makes sure to preserve all memory perfectly.
    uint val = reinterpret_cast<const uint&>(valRef);

    if (EndiannessUtils::isBigEndian())
        val = std::byteswap(val);

    while ((val & ~0x7F) != 0) {
        out << (val | 0x80);
        val >>= 7;
    }
    // operator<< was used previously, but I do not want changes there to affect this Codec.
    auto* valBytes = reinterpret_cast<unsigned char*>(&val);

    out.writeBytes(valBytes,
        valBytes + sizeof(uint));
}

int VarIntCodec::deserialize(TypedInputStream& in)
{
    int result = 0;
    int shift = 0;
    bool isLastByte = false;

    while (!isLastByte) {
        unsigned char b = 0;
        if (!(in >> b)) throw CodecParsingException(
            "Couldn't read from TypedInputStream. "
            "Perhaps EoF has been reached."
        );

        // cheat sheet for hex: 0 = 0000 1 = 0001 2 = 0010 3 = 0011 4 = 0100
        // 5 = 0101 6 = 0110 7 = 0111 8 = 1000 9 = 1001
        // A = 1010 B = 1011 C = 1100 D = 1101 E = 1110 F = 1111

        isLastByte = (b & 0x80) == 0;

        result |= (b & 0x7F) << shift;
        shift += 7;

        if (shift > 40)
        {
            Logger::warn("Cannot deserialize varint, it is too big.");
            break;
        }
    }
    if (EndiannessUtils::isBigEndian())
        result = std::byteswap(result);
    return result;
}
// PRIVATE
VarIntCodec::VarIntCodec() = default;