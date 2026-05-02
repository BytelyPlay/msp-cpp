module;

export module S2CPlayerPositionPacket;
import PacketS2C;
import PacketType;

export class S2CPlayerPositionPacket : public PacketS2C
{
public:
    PacketType& getPacketType() override;
public:
    // VarInt
    int teleportId {};

    double x {};
    double y {};
    double z {};

    double velocityX {};
    double velocityY {};
    double velocityZ {};

    float yaw {};
    float pitch {};

    int teleportFlags {};
};