#include "src/utils/stringfunctions.hpp"

/**
 * This function takes in a string and comma separates the characters into groups of three
 * @param strCpy the string to comma separate
 * @return the comma separated string
 */
std::string commaSeparate(const std::string& strCpy)
{
    std::string commaSeparated = strCpy;

    unsigned int commaCount = 0;
    //loop through entire string
    for(unsigned int index = commaSeparated.length(); index != 0; --index)
    {
        //checks to see if group of 3
        if((commaSeparated.length() - index - commaCount)%3 == 0 && index != commaSeparated.length())
        {
            commaSeparated.insert(index, 1, ',');
            ++commaCount;
        }
    }
    return commaSeparated;
}
