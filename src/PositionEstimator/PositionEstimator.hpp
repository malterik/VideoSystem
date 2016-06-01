#pragma once

#include "../CameraMatrix/CameraMatrix.hpp"
#include <vector>

class PositionEstimator
{
public:
  PositionEstimator(const CameraMatrix& leftCameraMatrix, const CameraMatrix& rightCameraMatrix);
  void triangulate(const std::vector<Eigen::Vector2d>& matchedPoints1, const std::vector<Eigen::Vector2d>& matchedPoints2);

private:
  CameraMatrix left_camera_matrix_;
  CameraMatrix right_camera_matrix_;
};
