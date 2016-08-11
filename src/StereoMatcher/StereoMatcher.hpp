#pragma once
#include "../Utils/DisableWarnings.hpp"
#include <vector>
#include <opencv2/opencv.hpp>
#include "../Eigen/Dense"

class StereoMatcher
{
public:
  StereoMatcher();
  std::vector<std::vector<cv::Point>> findPointPairs(const std::vector<cv::Rect> peopleL, const std::vector<cv::Rect> peopleR);

private:
  std::vector<Eigen::Vector2i> point_pairs_;
  const int THRESHOLD_;
};
