module;
#include <memory>
#include <string>


export module C2SLoginAcknowledgedPacketType;
import PacketTypeC2S;
import Phase;
import TypedInputStream;
import PacketC2S;


export class C2SLoginAcknowledgedPacketType : public PacketTypeC2S
{
public:
    static C2SLoginAcknowledgedPacketType& getInstance();
public:
    Phase getPhase() override;
    int getPacketID() override;

    std::string getPacketIdentifier() override;
public:
    std::unique_ptr<PacketC2S>
    deserialize(TypedInputStream& in) override;
private:
    C2SLoginAcknowledgedPacketType();
public:
    C2SLoginAcknowledgedPacketType(const C2SLoginAcknowledgedPacketType&) = delete;
    C2SLoginAcknowledgedPacketType operator=(const C2SLoginAcknowledgedPacketType&) = delete;

    C2SLoginAcknowledgedPacketType(C2SLoginAcknowledgedPacketType&&) = delete;
    C2SLoginAcknowledgedPacketType operator=(C2SLoginAcknowledgedPacketType&&) = delete;
};