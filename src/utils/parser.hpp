#pragma once

#include <vector>
#include <string>

std::vector<std::vector<std::string>> loadData(const std::string&);
void saveData(const std::string&, const std::vector<std::vector<std::string>>&);

