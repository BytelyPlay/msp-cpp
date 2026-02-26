module;
#include <algorithm>
#include <fstream>
#include <memory>

module TypedInputStream;
import FlexibleStreamBuf;
// PUBLIC
TypedInputStream::TypedInputStream(std::vector<unsigned char> data)
{
    streambufInternal_ =
        std::make_unique<FlexibleStreamBuf<unsigned char>>(
            data.data(),
            data.data() + data.size()
        );
    in =
        std::basic_istream
    (
        streambufInternal_.get()
    );

    dataInternal_ = data;
}

// PUBLIC
std::vector<unsigned char> TypedInputStream::readBytes(long long amount)
{
    unsigned char bytes[amount];
    in.readsome(bytes, amount);

    std::vector bytesVec(
        std::begin(bytes),
        std::end(bytes)
    );
    return bytesVec;
}
