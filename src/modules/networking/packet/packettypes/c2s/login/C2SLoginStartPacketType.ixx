module;
#include <memory>

export module C2SLoginStartPacketType;
import PacketTypeC2S;
import TypedInputStream;
import PacketC2S;
import Phase;

export class C2SLoginStartPacketType : public PacketTypeC2S
{
public:
    static C2SLoginStartPacketType& getInstance();

    std::unique_ptr<PacketC2S> deserialize(TypedInputStream& in) override;
public:
    Phase getPhase() override;
    int getPacketID() override;

    std::string getPacketIdentifier() override;
private:
    C2SLoginStartPacketType();
public:
    C2SLoginStartPacketType(const C2SLoginStartPacketType&) = delete;
    C2SLoginStartPacketType operator=(const C2SLoginStartPacketType&) = delete;

    C2SLoginStartPacketType(C2SLoginStartPacketType&&) = delete;
    C2SLoginStartPacketType operator=(C2SLoginStartPacketType&&) = delete;
};