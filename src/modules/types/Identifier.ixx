module;
#include <regex>
#include <string>

export module Identifier;

const std::regex NAMESPACE_VALID_REGEX = std::regex("^[a-z0-9.-_]+$");
const std::regex VALUE_VALID_REGEX = std::regex("^[a-z0-9.-_/]+$");

export struct Identifier
{
    bool isValid();

    std::string identifierNameSpace;
    std::string identifierValue;
};