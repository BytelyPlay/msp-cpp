module;

module GameProfileCodec;

// PUBLIC

// PUBLIC
GameProfileCodec& GameProfileCodec::getInstance()
{
    static GameProfileCodec codec;
    return codec;
}

void GameProfileCodec::serialize(const GameProfile& obj, TypedOutputStream& out)
{

}

GameProfile GameProfileCodec::deserialize(TypedInputStream& in)
{

}
// PRIVATE
GameProfileCodec::GameProfileCodec()
{

}
// PUBLIC
