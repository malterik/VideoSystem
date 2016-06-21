#pragma once

#include "../Utils/DisableWarnings.hpp"
#include "../Eigen/Dense"

#include <vector>
#include <string>
#include <fstream>
#include "../json/json.hpp"
#include "../Utils/TransformationMatrix.hpp"

using json = nlohmann::json;

class JSONParser
{
public:
  static JSONParser& getInstance();
  std::vector<Eigen::Vector2d> getVector(std::string filename);
  TransformationMatrix getTransformationMatrix(std::string filename);

private:
  JSONParser();
  JSONParser(const JSONParser& wm);
  unsigned int numberOfLines(std::ifstream file);
};
