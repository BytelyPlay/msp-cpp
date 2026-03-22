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

}

UUID UUIDCodec::deserialize(TypedInputStream& in)
{

}

// PRIVATE
UUIDCodec::UUIDCodec()
= default;

// PUBLIC
