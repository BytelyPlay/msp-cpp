module;
#include <regex>

module Identifier;

bool Identifier::isValid()
{
    return
    std::regex_match(identifierNameSpace, NAMESPACE_VALID_REGEX) &&
        std::regex_match(identifierValue, VALUE_VALID_REGEX);
}
