module;
#include <memory>


export module S2CPlayerPositionPacketType;
import PacketTypeS2C;
import PacketS2C;
import Phase;
import TypedOutputStream;


export class S2CPlayerPositionPacketType : public PacketTypeS2C
{
public:
    static S2CPlayerPositionPacketType& getInstance();
public:
    void serialize(std::unique_ptr<PacketS2C> packet,
        TypedOutputStream& out) override;
public:
    int getPacketID() override;
    std::string getPacketIdentifier() override;

    Phase getPhase() override;
private:
    S2CPlayerPositionPacketType();
public:
    S2CPlayerPositionPacketType(const S2CPlayerPositionPacketType&) = delete;
    S2CPlayerPositionPacketType operator=(const S2CPlayerPositionPacketType&) = delete;

    S2CPlayerPositionPacketType(S2CPlayerPositionPacketType&&) = delete;
    S2CPlayerPositionPacketType operator=(S2CPlayerPositionPacketType&&) = delete;
};