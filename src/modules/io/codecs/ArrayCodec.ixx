module;
#include <optional>
#include <vector>

export module ArrayCodec;
import Codec;
import TypedInputStream;
import TypedOutputStream;

export template<typename T>
class ArrayCodec : public Codec<std::vector<T>>
{
public:
    static ArrayCodec& getInstance(Codec<T>& codec);

    void serialize(
        const std::vector<T>& obj,
        TypedOutputStream& out
    ) override;
    std::vector<T> deserialize(
        TypedInputStream& in
    ) override;
private:
    Codec<std::vector<T>>& codec;
private:
    ArrayCodec(Codec<T>& codec);
public:
    ArrayCodec(const ArrayCodec&) = delete;
    ArrayCodec operator=(const ArrayCodec&) = delete;

    ArrayCodec(ArrayCodec&&) = delete;
    ArrayCodec operator=(ArrayCodec&&) = delete;
};