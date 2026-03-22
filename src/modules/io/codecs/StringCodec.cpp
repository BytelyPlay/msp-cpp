module;
#include <vector>
#include <string>

module StringCodec;
import VarIntCodec;

// PUBLIC
StringCodec& StringCodec::getInstance()
{
    static StringCodec codec;
    return codec;
}

void StringCodec::serialize(const std::string& obj, TypedOutputStream& out)
{
    VarIntCodec::getInstance().serialize(obj.size(), out);
    out.writeBytes(
        reinterpret_cast
        <const unsigned char*>(obj.data()),

        reinterpret_cast
        <const unsigned char*>(obj.data() + obj.size())
    );
}

std::string StringCodec::deserialize(TypedInputStream& in)
{
    std::vector<unsigned char> string;

    int size = VarIntCodec::getInstance().deserialize(in);
    in.readBytes(size, string);

    return { string.begin(), string.end() };
}

// PRIVATE
StringCodec::StringCodec()
= default;

// PUBLIC
