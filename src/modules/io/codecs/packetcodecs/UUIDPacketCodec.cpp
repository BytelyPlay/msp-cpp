module;
#include <optional>

module UUIDPacketCodec;
import Logger;
// PUBLIC
UUIDPacketCodec& UUIDPacketCodec::getInstance()
{
    static UUIDPacketCodec codec;
    return codec;
}

void UUIDPacketCodec::serialize(const UUID& obj, TypedOutputStream& out, bool& successful)
{
    out.writeBytes(obj.uuid.data(),
        obj.uuid.data() + obj.uuid.size());
}

std::optional<UUID> UUIDPacketCodec::deserialize(TypedInputStream& in)
{
    UUID uuid {};
    if (in.readBytes(uuid.uuid.data(),
        uuid.uuid.data() + uuid.uuid.size()) < uuid.uuid.size())
    {
        Logger::warn("Couldn't deserialize UUID, Likely EoF");
        return {};
    }
    return uuid;
}

// PRIVATE
UUIDPacketCodec::UUIDPacketCodec()
= default;

// PUBLIC
