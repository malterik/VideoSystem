#include "JSONParser.hpp"

JSONParser::JSONParser()
{
}

JSONParser& JSONParser::getInstance() {
  static JSONParser instance_;
  return instance_;
}

std::vector<Eigen::Vector2d> JSONParser::getVector(std::string filename)
{
  json vec;
  std::ifstream jsonFile(filename);
  std::vector<Eigen::Vector2d> result;
  if (jsonFile.is_open()) {
    unsigned int size = 0;
    std::string line;


    std::string str((std::istreambuf_iterator<char>(jsonFile)), std::istreambuf_iterator<char>());
    vec = json::parse(str);
    jsonFile.close();
    size = vec["size"];
    for(unsigned int i = 0; i < size; i++) {
      Eigen::Vector2d element(vec["vec"][i][0], vec["vec"][i][1]);
      result.push_back(element);
    }

  }else {
    std::cout << "Could not load file:" << filename << std::endl;
  }
  return result;
}

