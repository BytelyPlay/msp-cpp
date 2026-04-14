module;
#include <memory>

export module C2SClientInformationPacketType;
import PacketTypeC2S;
import TypedInputStream;
import PacketC2S;
import Phase;

export class C2SClientInformationPacketType : public PacketTypeC2S
{
public:
    static C2SClientInformationPacketType& getInstance();

    std::unique_ptr<PacketC2S> deserialize(TypedInputStream& in) override;
public:
    Phase getPhase() override;
    int getPacketID() override;

    std::string getPacketIdentifier() override;
private:
    C2SClientInformationPacketType();
public:
    C2SClientInformationPacketType(const C2SClientInformationPacketType&) = delete;
    C2SClientInformationPacketType operator=(const C2SClientInformationPacketType&) = delete;

    C2SClientInformationPacketType(C2SClientInformationPacketType&&) = delete;
    C2SClientInformationPacketType operator=(C2SClientInformationPacketType&&) = delete;
};