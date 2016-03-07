#include "CameraMatrix.hpp" 
#include "../json/json.hpp"
#include <iostream>
#include <fstream>
#include "../Utils/print.hpp"

using json = nlohmann::json;

CameraMatrix::CameraMatrix() : FILE_NAME_("config/CamMatrix.json") {

   readConfig(); 

   intrinsic_paramter_ = Eigen::MatrixXd::Zero(3,4);
   intrinsic_paramter_(0,0) = f_x_;
   intrinsic_paramter_(1,1) = f_y_;
   intrinsic_paramter_(0,2) = c_x_;
   intrinsic_paramter_(1,2) = c_y_;
   intrinsic_paramter_(2,2) = 1;

   intrinsic_paramter_inv_ = intrinsic_paramter_.block<3,3>(0,0).inverse();;    
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
    } else print(ERROR, "Unable to open CameraMatrix config file");
}

Eigen::Vector3d CameraMatrix::pixel2camera(const Eigen::Vector2i& pixelCoord) {

    Eigen::Vector3d pixelCoordHomo;
    Eigen::Vector3d cameraCoord;

    pixelCoordHomo(0) = pixelCoord(0);
    pixelCoordHomo(1) = pixelCoord(1);
    pixelCoordHomo(2) = 1;

    cameraCoord = intrinsic_paramter_inv_ * pixelCoordHomo;

    return cameraCoord;

        
}

Eigen::Vector2i CameraMatrix::camera2pixel(const Eigen::Vector3d& cameraCoord) {

    if(cameraCoord(0) <= 0.0f) {
        return Eigen::Vector2i(0,0) ;
    }

    Eigen::Vector3d pixelCoordHomo(0,0,0);
    Eigen::Vector2i pixelCoord(0,0);
    Eigen::Vector4d cameraCoordHomo;
    
    //Convert to homogenous coordinates
    cameraCoordHomo(0)=cameraCoord(0);
    cameraCoordHomo(1)=cameraCoord(1);
    cameraCoordHomo(2)=cameraCoord(2);
    cameraCoordHomo(3)= 1;

    pixelCoordHomo = intrinsic_paramter_ * cameraCoordHomo;
    pixelCoordHomo = pixelCoordHomo / cameraCoordHomo(2);

    pixelCoord(0) = (int) pixelCoordHomo(0);
    pixelCoord(1) = (int) pixelCoordHomo(1);

    return pixelCoord;
}
