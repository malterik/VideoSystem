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
  static JSONParser& getInstance();
  std::vector<Eigen::Vector2d> getVector(std::string filename);

private:
  JSONParser();
  JSONParser(const JSONParser& wm);
  unsigned int numberOfLines(std::ifstream file);
};
