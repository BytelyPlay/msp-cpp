module;
#include <string>

export module StringPacketCodec;
import PacketCodec;
import TypedInputStream;
import TypedOutputStream;

export class StringPacketCodec : public PacketCodec<std::string>
{
public:
    static StringPacketCodec& getInstance();

    using PacketCodec::serialize;
    using PacketCodec::deserialize;

    void serialize(const std::string& obj, TypedOutputStream& out) override;
    std::string deserialize(TypedInputStream& in) override;
private:
    StringPacketCodec();
public:
    StringPacketCodec(const StringPacketCodec&) = delete;
    StringPacketCodec operator=(const StringPacketCodec&) = delete;

    StringPacketCodec(StringPacketCodec&&) = delete;
    StringPacketCodec operator=(StringPacketCodec&&) = delete;
};