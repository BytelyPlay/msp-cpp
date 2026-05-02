module;
#include <memory>
#include <string>


export module C2SFinishConfigurationPacketType;
import PacketTypeC2S;
import Phase;
import TypedInputStream;
import PacketC2S;


export class C2SFinishConfigurationPacketType : public PacketTypeC2S
{
public:
    static C2SFinishConfigurationPacketType& getInstance();
public:
    Phase getPhase() override;
    int getPacketID() override;

    std::string getPacketIdentifier() override;
public:
    std::unique_ptr<PacketC2S>
    deserialize(TypedInputStream& in) override;
private:
    C2SFinishConfigurationPacketType();
public:
    C2SFinishConfigurationPacketType(const C2SFinishConfigurationPacketType&) = delete;
    C2SFinishConfigurationPacketType operator=(const C2SFinishConfigurationPacketType&) = delete;

    C2SFinishConfigurationPacketType(C2SFinishConfigurationPacketType&&) = delete;
    C2SFinishConfigurationPacketType operator=(C2SFinishConfigurationPacketType&&) = delete;
};