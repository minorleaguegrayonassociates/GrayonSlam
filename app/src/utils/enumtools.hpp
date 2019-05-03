#pragma once
#include <string>
#include <array>

/**
 * @file enumtools.hpp
 * @brief Converts a string representation to its enum type
 *
 * Takes in a string container and string and goes through the string
 * container until it finds a string that matches the input string.
 * The enum increments after each iteration and will return at the
 * same index as where the string was found within the string container.
 *
 * This function assumes that @a Enum starts from 0 and the enum
 * values increment by one.
 *
 * @param container Container of string representations for @a Enum
 * @param strEnum String in @a container
 * @return @a Enum value that @a strEnum represents
 */
template<typename Enum, typename Container = std::array<std::string,0>>
Enum getEnumValue(const Container& container, const std::string& strEnum)
{
    //Make sure value is set to the base enum
    Enum enumVal = static_cast<Enum>(0);

    /* Check each string in the container for a match */
    for(const std::string& string : container)
    {
        if(string == strEnum)
            return enumVal;
        else
            enumVal = static_cast<Enum>(enumVal + 1);
    }

    //This returns if the string container doesn't hold the requested string
    return enumVal;
}
