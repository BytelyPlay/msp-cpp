module;
#include <string>
module CodecParsingException;
import IOException;

// PUBLIC
CodecParsingException::CodecParsingException(std::string what) :
IOException(what) {}
