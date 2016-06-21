#pragma once

#include "../Utils/DisableWarnings.hpp"
#include "../CameraMatrix/CameraMatrix.hpp"
#include <vector>

enum Side {LEFT, RIGHT};
class PositionEstimator
{
public:
  PositionEstimator(const CameraMatrix& leftCameraMatrix, const CameraMatrix& rightCameraMatrix);
  PositionEstimator(CameraType camera1, std::string path1, CameraType camera2, std::string path2);
  std::vector<Eigen::Vector3d> triangulate(const std::vector<Eigen::Vector2d>& matchedPoints1, const std::vector<Eigen::Vector2d>& matchedPoints2);
  std::vector<Eigen::Vector3d> triangulate(const std::array<std::vector<Eigen::Vector2d>,2>& matchedPoints);
  CameraMatrix getCameraMatrix(Side cameraSide);

private:
  CameraMatrix left_camera_matrix_;
  CameraMatrix right_camera_matrix_;
};
