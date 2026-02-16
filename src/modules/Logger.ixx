module;
#include <string>

export module Logger;

export namespace Logger
{
    void debug(std::string s);
    void info(std::string s);
    void warn(std::string s);
    void error(std::string s);
}