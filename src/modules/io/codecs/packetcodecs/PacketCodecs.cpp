/* module;

module PacketCodecs;

// PUBLIC
// PUBLIC
template <typename T, typename... Pairs>
requires (PacketCodecs::IsValidPair<std::decay_t<Pairs>>::value && ...)
PacketCodec<T> PacketCodecs::createSequencedCodec(Pairs... getterAndCodec)
{
    g
}
*/