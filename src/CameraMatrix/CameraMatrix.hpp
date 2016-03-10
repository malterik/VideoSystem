#pragma once
#include <string>
#include "../Eigen/Dense"
#include "../Utils/TransformationMatrix.hpp"

class CameraMatrix
{
public:
    CameraMatrix();
    Eigen::Vector3d pixel2camera(const Eigen::Vector2i& pixelCoord);
    Eigen::Vector3d pixel2world(const Eigen::Vector2i& pixelCoord);

    Eigen::Vector2i camera2pixel(const Eigen::Vector3d& cameraCoord);
    Eigen::Vector2i world2pixel(Eigen::Vector3d& worldCoord);

private:

    void readConfig(); 

    double c_x_;
    double c_y_;
    double f_x_;
    double f_y_;

    Eigen::MatrixXd intrinsic_paramter_;
    Eigen::Matrix3d intrinsic_paramter_inv_;
    TransformationMatrix camera2ground_;
    TransformationMatrix camera2ground_inv_;

    std::string FILE_NAME_;

};
