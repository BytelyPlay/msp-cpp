module;
#include <memory>
#include <string>


export module C2SCustomPayloadPacketType;
import PacketTypeC2S;
import Phase;
import TypedInputStream;
import PacketC2S;


export class C2SCustomPayloadPacketType : public PacketTypeC2S
{
public:
    static C2SCustomPayloadPacketType& getInstance();
public:
    Phase getPhase() override;
    int getPacketID() override;

    std::string getPacketIdentifier() override;
public:
    std::unique_ptr<PacketC2S>
    deserialize(TypedInputStream& in) override;
private:
    C2SCustomPayloadPacketType();
public:
    C2SCustomPayloadPacketType(const C2SCustomPayloadPacketType&) = delete;
    C2SCustomPayloadPacketType operator=(const C2SCustomPayloadPacketType&) = delete;

    C2SCustomPayloadPacketType(C2SCustomPayloadPacketType&&) = delete;
    C2SCustomPayloadPacketType operator=(C2SCustomPayloadPacketType&&) = delete;
};