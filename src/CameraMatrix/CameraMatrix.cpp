#include "CameraMatrix.hpp"
#include "../json/json.hpp"
#include <iostream>
#include <fstream>
#include "../Utils/print.hpp"

using json = nlohmann::json;

CameraMatrix::CameraMatrix() :
    camera2ground_("config/Camera2Ground.json"),
    FILE_NAME_("config/CamMatrix.json")
{
    // Read the values from the json file
    readConfig();
    // Construct the Matrix
    intrinsic_paramter_ = Eigen::MatrixXd::Zero(3,4);
    intrinsic_paramter_(0,0) = f_x_;
    intrinsic_paramter_(1,1) = f_y_;
    intrinsic_paramter_(0,2) = c_x_;
    intrinsic_paramter_(1,2) = c_y_;
    intrinsic_paramter_(2,2) = 1;
    // Compute the inverse of the matrix once, because it is used more often
    intrinsic_paramter_inv_ = intrinsic_paramter_.block<3,3>(0,0).inverse();

    bottomRight2topLeft_ = Eigen::Matrix3d::Zero();
    bottomRight2topLeft_(0,0)= -1;
    bottomRight2topLeft_(1,1)= -1;
    bottomRight2topLeft_(2,2)=  1;
    bottomRight2topLeft_(0,2)=  640;
    bottomRight2topLeft_(1,2)=  480;
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

    Eigen::Vector3d pixelCoordHomo(pixelCoord(0), pixelCoord(1), 1);
    Eigen::Vector3d cameraCoord;


    cameraCoord = intrinsic_paramter_inv_ * pixelCoordHomo;

    return cameraCoord;
}

Eigen::Vector3d CameraMatrix::pixel2world(const Eigen::Vector2i& pixelCoord) {

    Eigen::Vector3d cameraCoord;
    Eigen::Vector3d worldCoord(0,0,0);

    cameraCoord = pixel2camera(pixelCoord);

    cameraCoord = camera2ground_.rotM() * cameraCoord;

    print(DEBUG," cameraCoord  " );
    std::cout << cameraCoord << std::endl;

    if(cameraCoord(2) == 0.0f){
        return worldCoord;
    }

    worldCoord(0) = camera2ground_.posV()(0) - camera2ground_.posV()(2) * cameraCoord(0) / cameraCoord(2);
    worldCoord(1) = camera2ground_.posV()(1) - camera2ground_.posV()(2) * cameraCoord(1) / cameraCoord(2);
    // robot_coordinates.x = camera2ground.posV.x - camera2ground.posV.z * camera_coordinates.x / camera_coordinates.z;
    // robot_coordinates.y = camera2ground.posV.y - camera2ground.posV.z * camera_coordinates.y / camera_coordinates.z;
    return worldCoord;
}

Eigen::Vector2i CameraMatrix::camera2pixel(const Eigen::Vector3d& cameraCoord) {

    // if the object lies behind the camera abort (z<0)
    if(cameraCoord(2) <= 0.0f) {
        return Eigen::Vector2i(0,0) ;
    }

    Eigen::Vector3d pixelCoordHomo(0,0,1);
    Eigen::Vector4d cameraCoordHomo(cameraCoord(0), cameraCoord(1), cameraCoord(2), 1);
    // Do pinhole projection
    pixelCoordHomo = intrinsic_paramter_ * cameraCoordHomo;
    // Normalize the homogenous coordinates
    pixelCoordHomo = pixelCoordHomo / pixelCoordHomo(2);

    // Transform the coordinates from the bottom right to the top left corner. (opencv uses this coordinate frame)
    pixelCoordHomo= bottomRight2topLeft_ * pixelCoordHomo;
    pixelCoordHomo = pixelCoordHomo / pixelCoordHomo(2);

    return Eigen::Vector2i((int) pixelCoordHomo(0), (int) pixelCoordHomo(1));
}

Eigen::Vector2i CameraMatrix::world2pixel(Eigen::Vector3d& worldCoord) {

    Eigen::Vector2i pixelCoord(0,0);
    Eigen::Vector3d cameraCoord(0,0,0);

    worldCoord(2) = 0;

    // cameraCoord = camera2ground_.inverse().rotM() * worldCoord;
    cameraCoord = camera2ground_.inverse().transform(worldCoord);

    pixelCoord = camera2pixel(cameraCoord);

    return pixelCoord;
}
