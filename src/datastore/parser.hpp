#pragma once

#include <fstream>
#include <fstream>
#include <stdexcept>
#include <vector>
#include <iostream>
#include <sstream>

std::vector<std::vector<std::string>> loadTeamData(std::string);
std::vector<std::vector<std::string>> loadDistanceData(std::string);
void teamParseDebug(std::string);
void distanceParseDebug(std::string);