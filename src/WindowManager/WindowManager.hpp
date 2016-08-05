#pragma once
#include "../Utils/DisableWarnings.hpp"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <vector>
#include <array>

class WindowManager
{
public:
  static WindowManager& getInstance();
  void addImage(cv::Mat image);
  void addImage(std::vector<cv::Mat> imageVector);
  cv::Mat drawBoundingBox( std::vector<cv::Rect> bBox, const cv::Mat& img);
  void drawBoundingBoxStereo(std::vector<std::vector<cv::Rect>> bBox, const cv::Mat& imgLeft, const cv::Mat& imgRight);
  void drawPointsStereo(std::vector<std::vector<cv::Point>>  pointPairs, const cv::Mat& imgLeft, const cv::Mat& imgRight);
  void drawCircle(cv::Point coord, cv::Scalar color, int index);
  cv::Mat& showMultipleImages(int rows );
  void reset();
  std::array<int,5> getInfo();

private:
  WindowManager();
  WindowManager(const WindowManager& wm);

  std::vector<cv::Mat> img_vector_;
  cv::Mat dst_;
  unsigned int dst_heigth_;
  unsigned int dst_width_;
  unsigned int dst_rows_;
  unsigned int dst_cols_;
};
