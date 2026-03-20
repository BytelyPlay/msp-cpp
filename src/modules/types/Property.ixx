module;
#include <string>
#include <optional>

export module Property;

export struct Property
{
    std::string name;
    std::string value;
    std::optional<std::string> signature;
};
