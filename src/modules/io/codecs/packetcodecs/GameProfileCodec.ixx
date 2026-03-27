module;
#include <string>

export module GameProfileCodec;
import PacketCodec;
import GameProfile;
import TypedOutputStream;
import TypedInputStream;
import PrefixedOptionalPacketCodec;

export class GameProfileCodec : public PacketCodec<GameProfile>
{
public:
   static GameProfileCodec& getInstance();

   using PacketCodec::serialize;
   using PacketCodec::deserialize;
public:
   void serialize(const GameProfile& obj, TypedOutputStream& out) override;
   GameProfile deserialize(TypedInputStream& in) override;
private:
   GameProfileCodec();
public:
   GameProfileCodec(const GameProfileCodec&) = delete;
   GameProfileCodec operator=(const GameProfileCodec&) = delete;

   GameProfileCodec(GameProfileCodec&&) = delete;
   GameProfileCodec operator=(GameProfileCodec&&) = delete;
};