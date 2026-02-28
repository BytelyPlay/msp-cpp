module;

module TypedOutputStream;
// PUBLIC
TypedOutputStream::TypedOutputStream()
= default;

// PUBLIC
void TypedOutputStream::writeBytes(const std::vector<unsigned char>& bytes)
{
    std::copy(
        bytes.begin(),
        bytes.end(),
        data
    );
}

// PUBLIC
std::vector<unsigned char> TypedOutputStream::getData()
{
    return data;
}

// PUBLIC
void TypedOutputStream::operator<<(const std::vector<unsigned char>& bytes)
{
    writeBytes(bytes);
}

void TypedOutputStream::operator<<(const unsigned char& byte)
{
    data.push_back(byte);
}
