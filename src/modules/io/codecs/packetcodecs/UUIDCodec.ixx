module;
#include <vector>

export module UUIDCodec;
import Codec;
import TypedInputStream;
import TypedOutputStream;
import UUID;

export class UUIDCodec : public Codec<UUID>
{
public:
    static UUIDCodec& getInstance();

    using Codec::serialize;
    using Codec::deserialize;

    void serialize(const UUID& obj, TypedOutputStream& out) override;
    UUID deserialize(TypedInputStream& in) override;
private:
    UUIDCodec();
public:
    UUIDCodec(const UUIDCodec&) = delete;
    UUIDCodec operator=(const UUIDCodec&) = delete;

    UUIDCodec(UUIDCodec&&) = delete;
    UUIDCodec operator=(UUIDCodec&&) = delete;
};