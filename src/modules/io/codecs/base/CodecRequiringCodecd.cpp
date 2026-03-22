module;

module CodecRequiringCodec;

// PUBLIC
// PUBLIC
template <typename T>
std::vector<unsigned char>
CodecRequiringCodec<T>::serialize
(const T& obj, Codec<T>& codec)
{
    TypedOutputStream out;
    serialize(obj, codec, out);

    return out.getData();
}

template <typename T>
T CodecRequiringCodec<T>::deserialize
(const std::vector<unsigned char>& data,
    Codec<T>& codec,
    uint& bytesConsumed)
{
    TypedInputStream in(data.data(),
        data.data() + data.size());
    return deserialize(in, codec);
}

// PUBLIC
