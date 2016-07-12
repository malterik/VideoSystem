#pragma once
#include <opencv2/opencv.hpp>

class ImageSubtractor {

public:
  ImageSubtractor(const cv::Mat& initialBackground);
  ImageSubtractor();
  void setBackground( const cv::Mat& img);
  cv::Mat& getBackground();
  cv::Mat& subtractBackground(const cv::Mat& img);
  cv::Mat& getDiffImage();

private:
  cv::Mat background_image_;
  cv::Mat diff_image_;

};
