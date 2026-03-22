module;
#include <string>

export module StringCodec;
import Codec;
import TypedInputStream;
import TypedOutputStream;

export class StringCodec : public Codec<std::string>
{
public:
    static StringCodec& getInstance();

    using Codec::serialize;
    using Codec::deserialize;

    void serialize(const std::string& obj, TypedOutputStream& out) override;
    std::string deserialize(TypedInputStream& in) override;
private:
    StringCodec();
public:
    StringCodec(const StringCodec&) = delete;
    StringCodec operator=(const StringCodec&) = delete;

    StringCodec(StringCodec&&) = delete;
    StringCodec operator=(StringCodec&&) = delete;
};