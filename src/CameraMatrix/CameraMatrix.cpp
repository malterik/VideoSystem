#include "CameraMatrix.hpp"
#include <iostream>
#include <fstream>
#include "../Utils/print.hpp"
#include "../json/json.hpp"
#include "../JSONParser/JSONParser.hpp"

using json = nlohmann::json;

CameraMatrix::CameraMatrix(CameraType camType, std::string camera2groundFile) :
    camera2ground_(JSONParser::getInstance().getTransformationMatrix(camera2groundFile)),
    cam_type_(camType)
{
  if(cam_type_ == IP_CAM1) {
    FILE_NAME_ = "config/IPCamMatrix.json";
  } else if(cam_type_ == LOCAL_CAM) {
    FILE_NAME_ = "config/CamMatrix.json";
  } else if(cam_type_ == DLINK_CAM_1) {
    FILE_NAME_ = "config/DLINK20Param.json";
  } else if(cam_type_ == DLINK_CAM_2) {
    FILE_NAME_ = "config/DLINK22Param.json";
  }

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

}
void CameraMatrix::readConfig() {

  json config;
  std::ifstream configFile(FILE_NAME_);
  if (configFile.is_open()) {
    std::string str((std::istreambuf_iterator<char>(configFile)), std::istreambuf_iterator<char>());
    config = json::parse(str);

    c_x_ = config["c_x"];
    c_y_ = config["c_y"];
    f_x_ = config["f_x"];
    f_y_ = config["f_y"];
    d_1_ = config["d"][0];
    d_2_ = config["d"][1];
    // print(LogLevel::DEBUG, "d_1: %f, d_2: %f",d_1_,d_2_);

    configFile.close();
  } else print(ERROR, "Unable to open File: %s", FILE_NAME_.c_str());
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
TransformationMatrix& CameraMatrix::getCamera2Ground() {
  return camera2ground_;
}

Eigen::Vector2d CameraMatrix::getDistortionCoefficients() {
  Eigen::Vector2d result;
  result[0] = d_1_;
  result[1] = d_2_;
  return result;
}
