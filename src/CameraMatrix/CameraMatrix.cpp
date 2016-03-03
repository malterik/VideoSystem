#include "CameraMatrix.hpp" 
#include "../json/json.hpp"
#include <iostream>
#include <fstream>

using json = nlohmann::json;

CameraMatrix::CameraMatrix() : FILE_NAME_("config/CamMatrix.json") {
   readConfig(); 
}

void CameraMatrix::readConfig() {

    json config; 
    std::cout << FILE_NAME_ << std::endl;
    std::ifstream configFile(FILE_NAME_);
    if (configFile.is_open()) {
        std::string str((std::istreambuf_iterator<char>(configFile)), std::istreambuf_iterator<char>());
        config = json::parse(str);    

        c_x_ = config["c_x"];
        c_y_ = config["c_y"];
        f_x_ = config["f_x"];
        f_y_ = config["f_y"];

        configFile.close();
    } else std::cout << "Unable to open CameraMatrix config file" << std::endl; 
}
