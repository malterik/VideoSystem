#pragma once

#include "../Eigen/Dense"

#include <vector>
#include <string>
#include <fstream>
#include "../json/json.hpp"

using json = nlohmann::json;

class JSONParser
{
public:
  JSONParser();
  std::vector<Eigen::Vector2d> getVector(std::string filename);

private:
  unsigned int numberOfLines(std::ifstream file);
};
