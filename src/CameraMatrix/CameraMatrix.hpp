#pragma once
#include <string>
#include "../Eigen/Dense"

class CameraMatrix
{
public:
    CameraMatrix();
    Eigen::Vector3d pixel2world(Eigen::Vector2i& pixelCoord);
    Eigen::Vector2i world2pixel(Eigen::Vector3d& pixelCoord);

private:

    void readConfig(); 

    double c_x_;
    double c_y_;
    double f_x_;
    double f_y_;
    Eigen::MatrixXd intrinsic_paramter_;

    std::string FILE_NAME_;

};
