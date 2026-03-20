module;
#include <memory>
#include <vector>

export module S2CLoginFinishedPacketType;
import PacketTypeS2C;
import PacketS2C;
import Phase;

export class S2CLoginFinishedPacketType : public PacketTypeS2C
{
public:
    static S2CLoginFinishedPacketType& getInstance();
public:
    std::vector<unsigned char> serialize(
        std::unique_ptr<PacketS2C>
    );
public:
    int getPacketID() override;
    std::string getPacketIdentifier() override;

    Phase getPhase() override;
private:
    S2CLoginFinishedPacketType();
public:
    S2CLoginFinishedPacketType(const S2CLoginFinishedPacketType&) = delete;
    S2CLoginFinishedPacketType operator=(const S2CLoginFinishedPacketType&) = delete;

    S2CLoginFinishedPacketType(S2CLoginFinishedPacketType&&) = delete;
    S2CLoginFinishedPacketType operator=(S2CLoginFinishedPacketType&&) = delete;
};