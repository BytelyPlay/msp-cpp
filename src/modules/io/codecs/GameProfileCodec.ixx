module;
#include <string>

export module GameProfileCodec;
import Codec;
import GameProfile;
import TypedOutputStream;
import TypedInputStream;
import PrefixedOptionalCodec;

export class GameProfileCodec : public Codec<GameProfile>
{
public:
   static GameProfileCodec& getInstance();

   using Codec::serialize;
   using Codec::deserialize;
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