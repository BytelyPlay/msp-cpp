module;
#include <stdexcept>

export module PacketParsingException;
import IOException;

export class PacketParsingException : public IOException
{
public:
    PacketParsingException(std::string what);
};