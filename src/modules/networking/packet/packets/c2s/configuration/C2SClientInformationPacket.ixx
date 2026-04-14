module;
#include <string>

export module C2SClientInformationPacket;
import PacketC2S;
import PacketType;
import ChatMode;
import MainHand;
import ParticleStatus;

export class C2SClientInformationPacket : public PacketC2S
{
public:
    PacketType& getPacketType() override;
public:
    std::string locale;
    char viewDistance;
    ChatMode chatMode;
    bool chatColors;
    // bitmask with the enum DisplayedSkinParts as a helper
    unsigned char displayedSkinParts;
    MainHand mainHand;
    bool enableTextFiltering;
    bool allowServerListings;
    ParticleStatus particleStatus;
};