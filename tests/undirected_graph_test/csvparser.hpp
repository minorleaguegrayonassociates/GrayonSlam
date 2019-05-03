#include <vector>
#include <sstream>
#include <fstream>
#include <string>

std::vector<std::vector<std::string>> loadData(const std::string& path)
{
    // Initializing - vector will hold all lines of data within the document
    std::vector<std::vector<std::string>> allRows;
    std::ifstream infile(path);

    std::string line;
    while (!infile.eof())
    {
        std::getline(infile, line);
        if (line.empty() || line.front() == '#' || line.front() == ' '){continue;}

        std::vector<std::string> columns;

        // used for seperating words
        std::stringstream row(line);
        std::string word;

        while (getline(row, word, ',')) //Extract until a comma
        {
            if(word.front() == '\"')
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
        }
        if(!columns.empty()){allRows.push_back(columns);}
    }
    infile.close();

    return allRows;
}
