#pragma once
#include "../Utils/DisableWarnings.hpp"
#include <string>
#include "../Eigen/Dense"
#include "../Utils/TransformationMatrix.hpp"
#include "../Utils/Utils.hpp"

class CameraMatrix
{
public:
  CameraMatrix(CameraType camType, std::string camera2groundFile);
  Eigen::MatrixXd getCameraMatrix();
  Eigen::MatrixXd getIntrinsicMatrix();
  Eigen::MatrixXd getExtrinsicMatrix();


private:

  void readConfig();

  double c_x_;
  double c_y_;
  double f_x_;
  double f_y_;
  double d_1_;
  double d_2_;

  Eigen::Matrix3d intrinsic_paramter_;
  Eigen::Matrix3d intrinsic_paramter_inv_;
  // Eigen::Matrix3d bottomRight2topLeft_;
  TransformationMatrix camera2ground_;

  std::string FILE_NAME_;
  CameraType cam_type_;

};
