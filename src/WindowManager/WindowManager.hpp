#pragma once
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
  void drawBoundingBox( std::vector<cv::Rect> bBox, const cv::Mat& img);
  cv::Mat& showMultipleImages(int rows );
  void reset();
  std::array<cv::Vec2i,5> getInfo();

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
