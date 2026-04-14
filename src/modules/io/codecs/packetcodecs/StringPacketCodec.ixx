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

    void serialize(const std::string& obj, TypedOutputStream& out, bool& successful) override;
    std::string deserialize(TypedInputStream& in, bool& successful) override;
private:
    StringPacketCodec();
};