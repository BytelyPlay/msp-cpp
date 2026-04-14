module;
#include <vector>

export module UUIDPacketCodec;
import PacketCodec;
import TypedInputStream;
import TypedOutputStream;
import UUID;

export class UUIDPacketCodec : public PacketCodec<UUID>
{
public:
    static UUIDPacketCodec& getInstance();

    using PacketCodec::serialize;
    using PacketCodec::deserialize;

    void serialize(const UUID& obj, TypedOutputStream& out, bool& successful) override;
    UUID deserialize(TypedInputStream& in, bool& successful) override;
private:
    UUIDPacketCodec();
};