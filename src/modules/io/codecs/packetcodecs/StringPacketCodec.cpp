module;
#include <vector>
#include <string>

module StringPacketCodec;
import VarIntPacketCodec;
import Logger;
import VarIntPacketCodec;

// PUBLIC
StringPacketCodec& StringPacketCodec::getInstance()
{
    static StringPacketCodec codec;
    return codec;
}

void StringPacketCodec::serialize(const std::string& obj, TypedOutputStream& out, bool& successful)
{
    VarIntPacketCodec::getInstance().serialize(obj.size(), out, successful);
    if (!successful) return;
    out.writeBytes(
        reinterpret_cast
        <const unsigned char*>(obj.data()),

        reinterpret_cast
        <const unsigned char*>(obj.data() + obj.size())
    );
    successful = true;
}

std::optional<std::string> StringPacketCodec::deserialize(TypedInputStream& in)
{
    std::vector<unsigned char> string;

    std::optional<int> optSize = VarIntPacketCodec::getInstance().deserialize(in);
    if (!optSize.has_value())
    {
        Logger::warn("VarIntPacketCodec can't read VarInt for prefixed String.");
        return {};
    };
    int size = optSize.value();

    size_t bytesRead = in.readBytes(size, string);

    if (bytesRead < size)
    {
        Logger::warn("Couldn't fully read String.");
        return {};
    }

    return { { string.begin(), string.end() } };
}

// PRIVATE
StringPacketCodec::StringPacketCodec()
= default;

// PUBLIC
