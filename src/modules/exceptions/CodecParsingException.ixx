module;

export module CodecParsingException;
#include <stdexcept>

export class CodecParsingException : public std::runtime_error
{
public:
    CodecParsingException(std::string what);
};
