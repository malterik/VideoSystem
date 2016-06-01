#include "CameraMatrix.hpp"
#include <iostream>
#include <fstream>
#include "../Utils/print.hpp"
#include "../json/json.hpp"

using json = nlohmann::json;

CameraMatrix::CameraMatrix(Camera camType, std::string camera2groundFile) :
    camera2ground_(camera2groundFile),
    cam_type_(camType)
{
  if(cam_type_ == IP_CAM) {
    FILE_NAME_ = "config/IPCamMatrix.json";
  } else if(cam_type_ == LOCAL_CAM) {
    FILE_NAME_ = "config/CamMatrix.json";
  }

  // Read the values from the json file
  readConfig();
  // Construct the Matrix
  intrinsic_paramter_ = Eigen::Matrix3d::Zero();
  intrinsic_paramter_(0,0) = f_x_;
  intrinsic_paramter_(1,1) = f_y_;
  intrinsic_paramter_(0,2) = c_x_;
  intrinsic_paramter_(1,2) = c_y_;
  intrinsic_paramter_(2,2) = 1;
  // Compute the inverse of the matrix once, because it is used more often
  intrinsic_paramter_inv_ = intrinsic_paramter_.inverse();

  // camera_matrix = intrinsic_paramter_ * camera2ground_.getMatrix();

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


Eigen::MatrixXd CameraMatrix::getCameraMatrix() {
  return intrinsic_paramter_ * camera2ground_.getSingularMatrix();
}

Eigen::MatrixXd CameraMatrix::getIntrinsicMatrix() {
  return intrinsic_paramter_;
}

Eigen::MatrixXd CameraMatrix::getExtrinsicMatrix() {
  return camera2ground_.getSingularMatrix();
}
