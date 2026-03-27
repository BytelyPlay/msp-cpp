module;

module UUIDPacketCodec;

// PUBLIC
UUIDPacketCodec& UUIDPacketCodec::getInstance()
{
    static UUIDPacketCodec codec;
    return codec;
}

void UUIDPacketCodec::serialize(const UUID& obj, TypedOutputStream& out)
{
    out.writeBytes(obj.uuid.data(),
        obj.uuid.data() + obj.uuid.size());
}

UUID UUIDPacketCodec::deserialize(TypedInputStream& in)
{
    UUID uuid {};
    in.readBytes(uuid.uuid.data(),
        uuid.uuid.data() + uuid.uuid.size());
    return uuid;
}

// PRIVATE
UUIDPacketCodec::UUIDPacketCodec()
= default;

// PUBLIC
