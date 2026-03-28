module;

export module GameProfilePacketCodec;
import PacketCodec;
import GameProfile;
import TypedInputStream;
import TypedOutputStream;

export class GameProfilePacketCodec : public PacketCodec<GameProfile>
{
public:
    static GameProfilePacketCodec& getInstance();

    void serialize(const GameProfile& obj, TypedOutputStream& out) override;
    GameProfile deserialize(TypedInputStream& in) override;
private:
    GameProfilePacketCodec();
};
