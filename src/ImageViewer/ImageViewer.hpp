#pragma once

#include <opencv2/opencv.hpp>
#include <string>

#include "../CameraInterface/CameraInterface.hpp"

class ImageViewer
{
public:
  ImageViewer(std::string windowName);
  void mouseCallback(int event, int x, int y);
  static void mouseCallback(int event, int x, int y, int, void* this_);
  void showImage(const cv::Mat& img);
  void dualView(const cv::Mat& img1, const cv::Mat& img2);
  void showCamera(Camera camera);
  void snapshots();

private:
  std::string window_name_;
  Camera camera_;
  CameraInterface camera_interface_;

  std::vector<cv::Point> image_coordinates_l_;
  std::vector<cv::Point> image_coordinates_r_;
  cv::RNG rng_;
  int color_counter_;
  cv::Scalar circle_color_;

};
