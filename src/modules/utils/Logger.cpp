module;
#include <iostream>

module Logger;

void Logger::debug(std::string s)
{
    std::cout << "[DEBUG] " << s << "\n";
}
void Logger::info(std::string s)
{
    std::cout << "[INFO] " << s << "\n";
}
void Logger::warn(std::string s)
{
    std::cout << "[WARN] " << s << "\n";
}
void Logger::error(std::string s)
{
    std::cout << "[ERROR] " << s << "\n";
}
