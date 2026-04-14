module;

export module PropertyPacketCodec;
import PacketCodec;
import Property;
import TypedInputStream;
import TypedOutputStream;

export class PropertyPacketCodec : public PacketCodec<Property>
{
public:
    static PropertyPacketCodec& getInstance();

    void serialize(const Property& obj, TypedOutputStream& out, bool& successful) override;
    Property deserialize(TypedInputStream& in, bool& successful) override;
private:
    PropertyPacketCodec();
};