module;

module IOStreamException;
import IOException;

// PUBLIC
IOStreamException::IOStreamException(std::string what) :
IOException(what) {}

