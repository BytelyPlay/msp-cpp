module;
#include <stdexcept>

module IOException;

// PUBLIC
IOException::IOException(std::string what) :
std::runtime_error(what) {}
