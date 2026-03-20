module;
#include <vector>
#include <memory>

export module PacketTypeS2C;
import PacketType;
import PacketS2C;
import Packet;
import Phase;

export class PacketTypeS2C : public PacketType
{
public:
    virtual std::vector<unsigned char> serialize(
        std::unique_ptr<PacketS2C>
    ) = 0;
public:
    int getPacketID() override = 0;
    std::string getPacketIdentifier() override = 0;
    Phase getPhase() override = 0;

    bool isC2S() override;
};
