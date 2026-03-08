module;
#include <string>
#include <stdexcept>

module CodecParsingException;

// PUBLIC
CodecParsingException::CodecParsingException(std::string what) :
std::runtime_error(what) {}
