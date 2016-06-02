#pragma once

#include <opencv2/opencv.hpp>
#include <string>

class ImageWriter
{
public:
  ImageWriter(const std::string& imageFolder);
  void writeImage(const cv::Mat& img, std::string filename);
  void resetCounter();

private:
  int counter_;
  std::string image_folder_;
};
