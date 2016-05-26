#pragma once

#include <vector>
#include <string>
#include <fstream>
#include "../json/json.hpp"

using json = nlohmann::json;

class JSONParser
{
public:
  JSONParser();
  std::vector<float> getVector(std::string filename);

private:
  unsigned int numberOfLines(std::ifstream file);
};
