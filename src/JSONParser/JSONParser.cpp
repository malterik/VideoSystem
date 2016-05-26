#include "JSONParser.hpp"

JSONParser::JSONParser()
{
}

std::vector<float> JSONParser::getVector(std::string filename)
{
  json vec;
  std::ifstream jsonFile(filename);
  if (jsonFile.is_open()) {
    int number_of_lines = 0;
    std::string line;

    while (std::getline(jsonFile , line)) {
      ++number_of_lines;
    }

    std::string str((std::istreambuf_iterator<char>(jsonFile)), std::istreambuf_iterator<char>());
    vec = json::parse(str);
    jsonFile.close();
    std::cout << "vector size" << number_of_lines<<  vec["vec"][0][0] << std::endl;

  }else {
    std::cout << "Could not load file:" << filename << std::endl;
  }
  return std::vector<float>();
}
unsigned int JSONParser::numberOfLines(std::ifstream file)
{
  // unsigned int lineCount = std::count(
  //     std::istream_iterator<char>(file),
  //     std::istream_iterator<char>(),
  //     '\n');
  // return lineCount;
  int number_of_lines = 0;
  std::string line;

  while (std::getline(file, line)) {
    ++number_of_lines;
  }
  return number_of_lines;
}
