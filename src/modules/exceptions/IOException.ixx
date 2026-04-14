module;
#include <stdexcept>

export module IOException;

export class IOException : public std::runtime_error
{
public:
    IOException(std::string what);
};