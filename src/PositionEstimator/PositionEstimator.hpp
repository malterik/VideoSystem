#pragma once

#include "../CameraMatrix/CameraMatrix.hpp"
#include <vector>

class PositionEstimator
{
public:
  PositionEstimator(const CameraMatrix& leftCameraMatrix, const CameraMatrix& rightCameraMatrix);
  PositionEstimator(Camera camera1, std::string path1, Camera camera2, std::string path2);
  void triangulate(const std::vector<Eigen::Vector2d>& matchedPoints1, const std::vector<Eigen::Vector2d>& matchedPoints2);
  void triangulate(const std::array<std::vector<Eigen::Vector2d>,2>& matchedPoints);

private:
  CameraMatrix left_camera_matrix_;
  CameraMatrix right_camera_matrix_;
};
