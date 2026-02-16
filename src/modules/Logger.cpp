module;

module Logger;
#include <iostream>

void Logger::debug(std::string s)
{
    std::cout << "[DEBUG] " + s;
}
void Logger::info(std::string s)
{
    std::cout << "[INFO] " + s;
}
void Logger::warn(std::string s)
{
    std::cout << "[WARN] " + s;
}
void Logger::error(std::string s)
{
    std::cout << "[ERROR] " + s;
}
