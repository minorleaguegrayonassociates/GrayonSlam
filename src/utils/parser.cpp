#include <fstream>
#include <sstream>
#include <iostream>
#include "parser.hpp"
#include "exceptions.hpp"

std::vector<std::vector<std::string>> loadData(const std::string& path)
{
    // Initializing - vector will hold all lines of data within the document
    std::vector<std::vector<std::string>> allRows;
    std::ifstream infile(path);

    if(path.substr(path.size()-4) != ".csv"){throw BadFileFormat(QString::fromUtf8("Wrong File type\n"), QString::fromStdString(path));}
    // Checks if file is open if not throw error
    if (!infile.is_open()){throw BadFile(QFile(QString::fromStdString(path)));}
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
    if (allRows.empty())
    {
        throw  BadFileFormat(QString::fromUtf8("Empty file!\n"), QString::fromStdString(path));
    }
    return allRows;
}

void saveData(const std::string& path, const std::vector<std::vector<std::string>>& allRows)
{
    // Creating a ofstream object that opens outfile with the given path
    std::ofstream outfile(path);

    // Check if path file extension matches expected file extension
    if(path.substr(path.size()-4) != ".csv"){throw BadFileFormat(QString::fromUtf8("Wrong File type\n"), QString::fromStdString(path));}
    // If file doesn't open throw BadFile error
    if (!outfile.is_open()){throw BadFile(QFile(QString::fromStdString(path)));}
    for(std::vector<std::string> columns: allRows)
    {
        /* Output first column before entering loop, first column doesn't need a comma preceding it, erase first column */
        outfile << columns.front();
        columns.erase(columns.begin());
        for(const std::string& column: columns)
        {
            /* Output each column with a comma preceding it */
            outfile << "," << column;
        }
        // Add a new line
        outfile << std::endl;
    }
    // Close outfile
    outfile.close();
}
