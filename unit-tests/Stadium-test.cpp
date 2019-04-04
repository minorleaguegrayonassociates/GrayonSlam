#include <iostream>
#include <iomanip>
#include <vector>
#include <cstdlib>
#include "../src/datastore/stadium.hpp"

std::string randomString(int length)
{
    std::string string;

    for(int i = 0; i < length; i++)
        string += rand() % ('Z' - 'A') + 'A';

    return string;
}

void printSouvenir(const Souvenir& souvenir)
{
    std::cout << std::left
              << std::setw(7) << "ID: "     << souvenir.getId()    << std::endl
              << std::setw(7) << "Name: "   << souvenir.getName()  << std::endl
              << std::setw(7) << "Price: $" << souvenir.getPrice() << std::endl
              << std::right;
}

int main()
{
    std::vector<Stadium> stadiums;

    /* Create stadiums and put them into the vector */
    for(int i = 0; i < 5; i++)
    {
        Stadium stadium(randomString(5), randomString(5));
        stadium.hidden = false;
        stadium.roof = static_cast<Stadium::Roof>(i % 3);
        stadium.surface = static_cast<Stadium::Surface>(i % 3);
        stadium.typology = static_cast<Stadium::Typology>(i % 6);

        for(int j = 0; j <= i; j++)
        {
            stadium.addSouvenir(randomString(3), j * 10);
        }

        stadiums.push_back(stadium);
    }

    /* Display each stadium's info */
    for(Stadium stadium : stadiums)
    {
        std::cout << std::setw(19) << "ID: "                << stadium.getId()                            << std::endl
                  << std::setw(19) << "Name: "              << stadium.getName()                          << std::endl
                  << std::setw(19) << "Location: "          << stadium.getLocation()                      << std::endl
                  << std::setw(19) << "Seat cap: "          << stadium.getSeatCap()                       << std::endl
                  << std::setw(19) << "Year opened: "       << stadium.getYearOpened()                    << std::endl
                  << std::setw(19) << "Center field dist: " << stadium.getCenterFieldDist()               << std::endl
                  << std::setw(19) << "Roof: "              << Stadium::ROOF_STRING[stadium.roof]         << std::endl
                  << std::setw(19) << "Surface: "           << Stadium::SURFACE_STRING[stadium.surface]   << std::endl
                  << std::setw(19) << "Typology: "          << Stadium::TYPOLOGY_STRING[stadium.typology] << std::endl;

        /* Display each souvenir in the stadium */
        for(Souvenir souvenir : stadium.getSouvenirs())
        {
            printSouvenir(souvenir);
        }
    }

    std::cout << std::endl << std::endl;

    /*
     * Test findSouvenir by going through each of the stadiums
     * and find souvenirs with IDs of [0, vector size).
     * Print out the information of that souvenir regardless
     * whether or not it's an invalid souvenir (ID = -1).
     */
    std::cout << "Testing Stadium::findSouvenir()...\n";

    for(Stadium stadium : stadiums)
    {
        for(int i = 0; i < stadiums.size(); i++)
        {
            Souvenir souvenir = stadium.findSouvenir(i);
            printSouvenir(souvenir);
        }

        std::cout << std::endl;
    }
    
    return 0;
}
