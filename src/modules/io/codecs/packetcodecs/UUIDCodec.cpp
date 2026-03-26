module;

module UUIDCodec;

// PUBLIC
UUIDCodec& UUIDCodec::getInstance()
{
    static UUIDCodec codec;
    return codec;
}

void UUIDCodec::serialize(const UUID& obj, TypedOutputStream& out)
{
    out.writeBytes(obj.uuid.data(),
        obj.uuid.data() + obj.uuid.size());
}

UUID UUIDCodec::deserialize(TypedInputStream& in)
{
    UUID uuid {};
    in.readBytes(uuid.uuid.data(),
        uuid.uuid.data() + uuid.uuid.size());
    return uuid;
}

// PRIVATE
UUIDCodec::UUIDCodec()
= default;

// PUBLIC
