module;
#include <memory>


export module S2CFinishConfigurationPacketType;
import PacketTypeS2C;
import PacketS2C;
import Phase;
import TypedOutputStream;


export class S2CFinishConfigurationPacketType : public PacketTypeS2C
{
public:
    static S2CFinishConfigurationPacketType& getInstance();
public:
    void serialize(std::unique_ptr<PacketS2C> packet,
        TypedOutputStream& out) override;
public:
    int getPacketID() override;
    std::string getPacketIdentifier() override;

    Phase getPhase() override;
private:
    S2CFinishConfigurationPacketType();
public:
    S2CFinishConfigurationPacketType(const S2CFinishConfigurationPacketType&) = delete;
    S2CFinishConfigurationPacketType operator=(const S2CFinishConfigurationPacketType&) = delete;

    S2CFinishConfigurationPacketType(S2CFinishConfigurationPacketType&&) = delete;
    S2CFinishConfigurationPacketType operator=(S2CFinishConfigurationPacketType&&) = delete;
};