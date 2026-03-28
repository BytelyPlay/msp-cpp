module;
#include <vector>
#include <string>

module StringPacketCodec;
import VarIntPacketCodec;
import Logger;
import CodecParsingException;

// PUBLIC
StringPacketCodec& StringPacketCodec::getInstance()
{
    static StringPacketCodec codec;
    return codec;
}

void StringPacketCodec::serialize(const std::string& obj, TypedOutputStream& out)
{
    VarIntPacketCodec::getInstance().serialize(obj.size(), out);
    out.writeBytes(
        reinterpret_cast
        <const unsigned char*>(obj.data()),

        reinterpret_cast
        <const unsigned char*>(obj.data() + obj.size())
    );
}

std::string StringPacketCodec::deserialize(TypedInputStream& in)
{
    std::vector<unsigned char> string;

    int size = VarIntPacketCodec::getInstance().deserialize(in);
    size_t bytesRead = in.readBytes(size, string);

    if (bytesRead < size)
        throw CodecParsingException("Couldn't fully read String.");

    return { string.begin(), string.end() };
}

// PRIVATE
StringPacketCodec::StringPacketCodec()
= default;

// PUBLIC
