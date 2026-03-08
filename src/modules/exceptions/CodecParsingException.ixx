module;
#include <stdexcept>

export module CodecParsingException;

export class CodecParsingException : public std::runtime_error
{
public:
    CodecParsingException(std::string what);
};
