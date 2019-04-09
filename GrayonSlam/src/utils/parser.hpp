#pragma once

#include <vector>
#include <string>
#include "../datastore/souvenir.hpp"
#include "../datastore/stadium.hpp"
#include "../datastore/team.hpp"

std::vector<std::vector<std::string>> loadData(const std::string&);
void saveData(const std::string&,std::vector<Team>&,std::vector<Stadium>&);
void teamParseDebug(const std::string&);
void distanceParseDebug(const std::string&);
