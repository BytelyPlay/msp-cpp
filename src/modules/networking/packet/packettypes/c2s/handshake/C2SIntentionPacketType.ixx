module;
#include <memory>
#include <string>

export module C2SIntentionPacketType;
import PacketTypeC2S;
import Phase;
import TypedInputStream;
import PacketC2S;
import C2SIntentionPacket;

export class C2SIntentionPacketType : public PacketTypeC2S
{
public:
    static C2SIntentionPacketType& getInstance();
public:
    Phase getPhase() override;
    int getPacketID() override;

    std::string getPacketIdentifier() override;
public:
    std::unique_ptr<PacketC2S>
    deserialize(TypedInputStream& in) override;
private:
    C2SIntentionPacketType();
};