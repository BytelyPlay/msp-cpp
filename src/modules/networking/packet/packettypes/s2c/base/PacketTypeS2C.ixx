module;
#include <vector>
#include <memory>

export module PacketTypeS2C;
import PacketType;
import PacketS2C;
import Packet;
import Phase;
import TypedOutputStream;

export class PacketTypeS2C : public PacketType
{
public:
    virtual void serialize(
        std::unique_ptr<PacketS2C> packet,
        TypedOutputStream& out,
        bool& success
    ) = 0;

    std::vector<unsigned char> serialize(
        std::unique_ptr<PacketS2C>,
        bool& success
    );
public:
    int getPacketID() override = 0;
    std::string getPacketIdentifier() override = 0;
    Phase getPhase() override = 0;

    bool isC2S() override;
};
