#include "parser.hpp"
#include "src/utils/exceptions.hpp"

void teamParseDebug(const std::string& path)
{
    std::vector<std::vector<std::string>> teamData = loadData(path);
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

void distanceParseDebug(const std::string & path)
{
    std::vector<std::vector<std::string>> distanceData = loadData(path);
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

std::vector<std::vector<std::string>> loadData(const std::string& path)
{
    // Initializing - vector will hold all lines of data within the document
    std::vector<std::vector<std::string>> allRows;
    std::ifstream infile(path, std::ios::in);
    int lineCount = 0;

    // Checks if file is open if not throw error
    if (!infile.is_open()){throw BadFile(QFile::tr(path.c_str()));}
    std::string line;
    while (infile.good())
    {
        std::getline(infile, line);
        if (!infile.eof())
        {
            if (line[0] == '#' || line[0] == ' '){continue;}

            ++lineCount;

            std::vector<std::string> columns;

            // used for seperating words
            std::stringstream row(line);
            std::string word;
            std::string wordQuotes;
            int wordCount = 0;

            while (getline(row, word, ','))
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
            allRows.push_back(columns);
        }
    }
    infile.close();
    if (lineCount == 0)
    {
        throw  BadFileFormat(QString::fromUtf8("*.csv"), QString::fromStdString(path));
    }
    return allRows;
}


