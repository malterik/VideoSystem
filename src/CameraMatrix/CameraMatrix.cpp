#include "CameraMatrix.hpp" 
#include "../json/json.hpp"
#include <iostream>
#include <fstream>

using json = nlohmann::json;

CameraMatrix::CameraMatrix() : FILE_NAME_("config/CamMatrix.json") {
   readConfig(); 

   intrinsic_paramter_ = Eigen::MatrixXd::Zero(3,4);
   intrinsic_paramter_(0,0) = f_x_;
   intrinsic_paramter_(1,1) = f_y_;
   intrinsic_paramter_(0,2) = c_x_;
   intrinsic_paramter_(1,2) = c_y_;
   intrinsic_paramter_(2,2) = 1;

   std::cout << intrinsic_paramter_ << std::endl;
   
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

Eigen::Vector3d CameraMatrix::pixel2world(Eigen::Vector2i& pixelCoord) {

    Eigen::Vector3d pixelInCameraCoords;
    pixelInCameraCoords(0) = (double) pixelCoord(0) - c_x_;
    pixelInCameraCoords(1) = (double) pixelCoord(1) - c_y_;
    pixelInCameraCoords(2) = f_x_;

    pixelInCameraCoords = intrinsic_paramter_.inverse() * pixelInCameraCoords;
    return pixelInCameraCoords;
        
}

Eigen::Vector2i CameraMatrix::world2pixel(Eigen::Vector3d& worldCoord) {
    Eigen::Vector4d worldCoordHomo;
    Eigen::Vector3d cameraCoord;
    Eigen::Vector2i pixelCoord;
    for (unsigned int i = 0; i < 3; i++) {
        worldCoordHomo(i) = worldCoord(i);
    }
    worldCoordHomo(3) = 1;
    cameraCoord = intrinsic_paramter_ * worldCoordHomo;
    std::cout << cameraCoord << std::endl;
    pixelCoord(0) = cameraCoord(0) / cameraCoord(2);
    pixelCoord(1) = cameraCoord(1) / cameraCoord(2);
    return pixelCoord;
}
