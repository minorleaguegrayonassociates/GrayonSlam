#include <iostream>
#include <iomanip>
#include <vector>
#include <cstdlib>
#include "../src/datastore/souvenir.hpp"

std::string randomString(int length)
{
    std::string string;

    for(int i = 0; i < length; i++)
        string += rand() % ('Z' - 'A') + 'A';

    return string;
}

int main()
{
    std::vector<Souvenir> souvenirs;

    /* Create souvenirs and put them into the vector */
    for(int i = 0; i < 10; i++)
    {
        Souvenir souvenir(randomString(5), i * 100);
        souvenir.hidden = false;

        souvenirs.push_back(souvenir);
    }

    /* Display each team's info */
    for(Souvenir souvenir : souvenirs)
    {
        std::cout << std::setw(7) << "ID: "    << souvenir.getId()    << std::endl
                  << std::setw(7) << "Name: "  << souvenir.getName()  << std::endl
                  << std::setw(7) << "Price: $" << souvenir.getPrice() << std::endl
                  << std::endl;
    }
    
    return 0;
}
