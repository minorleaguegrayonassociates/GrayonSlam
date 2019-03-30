#include "parser.hpp"

void teamParseDebug(std::string path)
{
    std::vector<std::vector<std::string>> teamData = loadTeamData(path);
    for (std::vector<std::vector<std::string>>::iterator it = teamData.begin(); it != teamData.end(); ++it)
    {
        std::cout << "----------Team ID: " << (*it)[0] << std::endl;
        std::cout << "--------Team Name: " << (*it)[1] << std::endl;
        std::cout << "---------Deleted?: " << (*it)[2] << std::endl;
        std::cout << "-------Stadium ID: " << (*it)[3] << std::endl;
        std::cout << "-----Stadium Name: " << (*it)[4] << std::endl;
        std::cout << "-Seating Capacity: " << (*it)[5] << std::endl;
        std::cout << "----Team Location: " << (*it)[6] << std::endl;
        std::cout << "--Playing Surface: " << (*it)[7] << std::endl;
        std::cout << "-----------League: " << (*it)[8] << std::endl;
        std::cout << "------Date opened: " << (*it)[9] << std::endl;
        std::cout << "--Distance2CtrFld: " << (*it)[10] << std::endl;
        std::cout << "Ballpark typology: " << (*it)[11] << std::endl;
        std::cout << "--------Roof Type: " << (*it)[12] << std::endl;
        std::cout << "NumberOSouvenirs:  " << (*it)[13] << std::endl;
        std::cout << "Souvenir ID:  " << (*it)[14] << std::endl;
        std::cout << "Is deleted?:  " << (*it)[15] << std::endl;
        std::cout << "---Souvenir:  " << (*it)[16] << std::endl;
        std::cout << "------Price:  " << (*it)[17] << std::endl;
        std::cout << "Souvenir ID:  " << (*it)[18] << std::endl;
        std::cout << "Is deleted?:  " << (*it)[19] << std::endl;
        std::cout << "---Souvenir:  " << (*it)[20] << std::endl;
        std::cout << "------Price:  " << (*it)[21] << std::endl;
        std::cout << "Souvenir ID:  " << (*it)[22] << std::endl;
        std::cout << "Is deleted?:  " << (*it)[23] << std::endl;
        std::cout << "---Souvenir:  " << (*it)[24] << std::endl;
        std::cout << "------Price:  " << (*it)[25] << std::endl;
        std::cout << "Souvenir ID:  " << (*it)[26] << std::endl;
        std::cout << "Is deleted?:  " << (*it)[27] << std::endl;
        std::cout << "---Souvenir:  " << (*it)[28] << std::endl;
        std::cout << "------Price:  " << (*it)[29] << std::endl;
        std::cout << "Souvenir ID:  " << (*it)[30] << std::endl;
        std::cout << "Is deleted?:  " << (*it)[31] << std::endl;
        std::cout << "---Souvenir:  " << (*it)[32] << std::endl;
        std::cout << "------Price:  " << (*it)[33] << std::endl;
        std::cout << std::endl;
    }
}

void distanceParseDebug(std::string path)
{
    std::vector<std::vector<std::string>> distanceData = loadDistanceData(path);
    for (std::vector<std::vector<std::string>>::iterator it = distanceData.begin(); it != distanceData.end(); ++it)
    {

        std::cout << "Stadium ID:   " << (*it)[0] << std::endl;
        std::cout << "Stadium Name: " << (*it)[1] << std::endl;
        std::cout << "Stadium ID:   " << (*it)[2] << std::endl;
        std::cout << "Stadium Name: " << (*it)[3] << std::endl;
        std::cout << "Distance:     " << (*it)[4] << std::endl;
        std::cout << std::endl;
    }
}

std::vector<std::vector<std::string>> loadTeamData(std::string path)
{
    // Initializing - vector will hold all lines of data within the document
    std::vector<std::vector<std::string>> allRows;
    std::ifstream infile(path, std::ios::in);
    int lineCount = 0;

    // Checks if file is open if now throw error
    if (infile.is_open())
    {
        std::string line;
        while (infile.good())
        {
            std::getline(infile, line);
            if (!infile.eof())
            {
                if (line[0] == '#' || line[0] == ' ')
                {
                    continue; // ignore comment lines and spaces
                }

                ++lineCount;

                std::vector<std::string> columns;

                // used for seperating words
                std::stringstream row(line);
                std::string word;
                int wordCount(0);

                while (!row.eof())
                {
                    if (wordCount < 5 || wordCount > 6)
                    {
                        getline(row, word, ',');
                    }
                    else
                    { // If  column 4 or 5 get what's between the quotes
                        std::getline(std::getline(row, word, '\"'), word, '\"');
                        row.ignore(1, ','); 
                    }
                    columns.push_back(word);
                    ++wordCount;
                }
                allRows.push_back(columns);
            }
        }
        infile.close();
    }
    else
    {
        throw std::invalid_argument("Team File name invalid");
    }
    if (lineCount == 0)
    {
        throw std::invalid_argument("Team File Empty");
    }
    return allRows;
}

std::vector<std::vector<std::string>> loadDistanceData(std::string path)
{
    // Initializing - vector will hold all lines of data within the document
    std::vector<std::vector<std::string>> allRows;
    std::ifstream infile(path, std::ios::in);
    int lineCount = 0;

    // Checks if file is open if now throw error
    if (infile.is_open())
    {
        std::string line;
        while (infile.good())
        {
            std::getline(infile, line);
            if (!infile.eof())
            {
                if (line[0] == '#' || line[0] == ' ')
                {
                    continue; // ignore comment lines and spaces
                }
                ++lineCount;

                std::vector<std::string> columns;
                // used for seperating words
                std::stringstream row(line);
                std::string word;

                while (getline(row, word, ','))
                {
                    columns.push_back(word);
                }
                allRows.push_back(columns);
            }
        }
        infile.close();
    }
    else
    {
        throw std::invalid_argument("Distance File name invalid");
    }
    if (lineCount == 0)
    {
        throw std::invalid_argument("Distance File Empty");
    }
    return allRows;
}