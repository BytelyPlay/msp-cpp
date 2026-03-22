module;
#include <vector>

export module ArrayCodec;
import Codec;

export class ArrayCodec : public Codec<std::vector<>>