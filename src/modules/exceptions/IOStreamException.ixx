module;
#include <string>

export module IOStreamException;
import IOException;

export class IOStreamException : public IOException
{
public:
    IOStreamException(std::string what);
};