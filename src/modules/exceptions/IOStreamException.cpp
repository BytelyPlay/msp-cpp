module;
#include <string>

module IOStreamException;
import IOException;

// PUBLIC
IOStreamException::IOStreamException(std::string what) :
IOException(what) {}

