module;
#include <string>
export module CodecParsingException;
import IOException;

export class CodecParsingException : public IOException
{
public:
    CodecParsingException(std::string what);
};
