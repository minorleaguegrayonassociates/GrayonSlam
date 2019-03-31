#include <fstream>
#include <sstream>
#include <iostream>
#include "parser.hpp"
#include "src/utils/exceptions.hpp"

void teamParseDebug(const std::string& path)
{
    std::vector<std::vector<std::string>> teamData = loadData(path);
    for (const std::vector<std::string>& team : teamData)
    {
        std::cout << "----------Team ID: " << team[0] << std::endl;
        std::cout << "--------Team Name: " << team[1] << std::endl;
        std::cout << "---------Deleted?: " << team[2] << std::endl;
        std::cout << "-------Stadium ID: " << team[3] << std::endl;
        std::cout << "-----Stadium Name: " << team[4] << std::endl;
        std::cout << "-Seating Capacity: " << team[5] << std::endl;
        std::cout << "----Team Location: " << team[6] << std::endl;
        std::cout << "--Playing Surface: " << team[7] << std::endl;
        std::cout << "-----------League: " << team[8] << std::endl;
        std::cout << "------Date opened: " << team[9] << std::endl;
        std::cout << "--Distance2CtrFld: " << team[10] << std::endl;
        std::cout << "Ballpark typology: " << team[11] << std::endl;
        std::cout << "--------Roof Type: " << team[12] << std::endl;
        std::cout << "NumberOSouvenirs:  " << team[13] << std::endl;
        std::cout << "Souvenir ID:  " << team[14] << std::endl;
        std::cout << "Is deleted?:  " << team[15] << std::endl;
        std::cout << "---Souvenir:  " << team[16] << std::endl;
        std::cout << "------Price:  " << team[17] << std::endl;
        std::cout << "Souvenir ID:  " << team[18] << std::endl;
        std::cout << "Is deleted?:  " << team[19] << std::endl;
        std::cout << "---Souvenir:  " << team[20] << std::endl;
        std::cout << "------Price:  " << team[21] << std::endl;
        std::cout << "Souvenir ID:  " << team[22] << std::endl;
        std::cout << "Is deleted?:  " << team[23] << std::endl;
        std::cout << "---Souvenir:  " << team[24] << std::endl;
        std::cout << "------Price:  " << team[25] << std::endl;
        std::cout << "Souvenir ID:  " << team[26] << std::endl;
        std::cout << "Is deleted?:  " << team[27] << std::endl;
        std::cout << "---Souvenir:  " << team[28] << std::endl;
        std::cout << "------Price:  " << team[29] << std::endl;
        std::cout << "Souvenir ID:  " << team[30] << std::endl;
        std::cout << "Is deleted?:  " << team[31] << std::endl;
        std::cout << "---Souvenir:  " << team[32] << std::endl;
        std::cout << "------Price:  " << team[33] << std::endl;
        std::cout << std::endl;
    }
}

void distanceParseDebug(const std::string& path)
{
    std::vector<std::vector<std::string>> distanceData = loadData(path);
    for (const std::vector<std::string>& stadiumDistance : distanceData)
    {

        std::cout << "Stadium ID:   " << stadiumDistance[0] << std::endl;
        std::cout << "Stadium Name: " << stadiumDistance[1] << std::endl;
        std::cout << "Stadium ID:   " << stadiumDistance[2] << std::endl;
        std::cout << "Stadium Name: " << stadiumDistance[3] << std::endl;
        std::cout << "Distance:     " << stadiumDistance[4] << std::endl;
        std::cout << std::endl;
    }
}

std::vector<std::vector<std::string>> loadData(const std::string& path)
{
    // Initializing - vector will hold all lines of data within the document
    std::vector<std::vector<std::string>> allRows;
    std::ifstream infile(path);
    int lineCount = 0;

    if(path.substr((path.size()-4)) != ".csv"){throw BadFileFormat(QString::fromUtf8("Wrong File type\n"), QString::fromStdString(path));}
    // Checks if file is open if not throw error
    if (!infile.is_open()){throw BadFile(QFile(QString::fromUtf8("Wrong File Path\n")));}
    std::string line;
    while (!infile.eof())
    {
        line.clear();
        std::getline(infile, line);
        if (line[0] == '#' || line[0] == ' ') {continue; }

        ++lineCount;

        std::vector<std::string> columns;

        // used for seperating words
        std::stringstream row(line);
        std::string word;
        int wordCount = 0;

        while (getline(row, word, ',')) //Extract until a comma
        {
            if(word[0] == '\"')
            {
                word.erase(0, 1); //Erase quotation mark

                std::string extra;
                bool finish = false;

                do
                {
                    std::getline(row, extra, ','); //Extra until a comma

                    if(extra.back() == '\"')
                    {
                        extra.erase(extra.size() - 1, 1); //Remove quotation mark at the end
                        finish = true;
                    }
                    word += ',' + extra;
                } while(!finish);
            }
            columns.push_back(word);
            ++wordCount;
        }
        if(!columns.empty()){allRows.push_back(columns);}
    }
    infile.close();
    if (lineCount == 0)
    {
        std::cout << path << std::endl;
        throw  BadFileFormat(QString::fromUtf8("Empty file!\n"), QString::fromStdString(path));
    }
    return allRows;
}


