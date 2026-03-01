module;

module CodecParsingException;

// PUBLIC
CodecParsingException::CodecParsingException(std::string what) :
std::runtime_error(what) {}
