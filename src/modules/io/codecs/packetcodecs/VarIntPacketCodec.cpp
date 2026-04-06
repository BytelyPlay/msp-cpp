module;
#include <string>
#include <cstdint>

module VarIntPacketCodec;
import EndiannessUtils;
import Logger;
import CodecParsingException;

// PUBLIC
VarIntPacketCodec& VarIntPacketCodec::getInstance()
{
    static VarIntPacketCodec codec;
    return codec;
}

void VarIntPacketCodec::serialize(const int& valRef, TypedOutputStream& out)
{
    uint val = reinterpret_cast<const uint&>(valRef);
    if (EndiannessUtils::isBigEndian()) val = std::byteswap(val);

    // val = 0b0000 0000 0000 0000 0000 0000 1000 0001

    while (true)
    {
        if ((val & 0xFFFFFF80) == 0)
        {
            // 0000 0001
            out << getFirstByte(val);
            break;
        }
        // val = 1000 0001
        out.writeByte(getFirstByte(val) | 0x80);

        // val = 0b0000 0000 0000 0000 0000 0000 0000 0001
        val >>= 7;

        // 0000 0000 0000 0000
    }
}

int VarIntPacketCodec::deserialize(TypedInputStream& in)
{
    // TODO: rewrite if needed

    int result = 0;
    int shift = 0;
    bool isLastByte = false;

    while (!isLastByte) {
        unsigned char b = 0;
        if (!(in >> b)) throw CodecParsingException(
            "Couldn't read from TypedInputStream to deserialize VarInt."
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
    return result;
}
// PRIVATE
VarIntPacketCodec::VarIntPacketCodec()
= default;

// PRIVATE
unsigned char VarIntPacketCodec::getFirstByte(uint val)
{
    return reinterpret_cast<unsigned char*>(&val)[0];
}
