module;
#include <string>
module PacketParsingException;
import IOException;

// PUBLIC
PacketParsingException::PacketParsingException(std::string what) :
IOException(what) {}

