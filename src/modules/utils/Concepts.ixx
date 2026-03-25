module;
#include <concepts>
#include <string>

export module Concepts;

export namespace Concepts
{
    template <typename T>
    concept Fundamental = std::is_fundamental_v<T>;

    template <typename T>
    concept String = std::same_as<std::decay_t<T>, std::string>;
}
