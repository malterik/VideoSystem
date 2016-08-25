#pragma once
#include "../Utils/DisableWarnings.hpp"
#include <opencv2/opencv.hpp>
#include <vector>
#include "../Eigen/Dense"

class Visualizer
{
public:
  Visualizer();
  cv::Mat& showMap(std::vector<Eigen::Vector3d> points);

private:
  void clearMap();

  cv::Mat map_;

};
