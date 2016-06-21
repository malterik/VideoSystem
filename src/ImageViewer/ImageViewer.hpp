#pragma once

#include "../Utils/DisableWarnings.hpp"
#include <opencv2/opencv.hpp>
#include <string>

#include "../CameraInterface/CameraInterface.hpp"
#include "../ImageWriter/ImageWriter.hpp"
#include "../Eigen/Dense"

enum CameraSide { LEFT_CAM, RIGHT_CAM, BOTH  };

class ImageViewer
{
public:
  ImageViewer(std::string windowName, Camera camLeft, Camera camRight);
  void mouseCallback(int event, int x, int y);
  static void mouseCallback(int event, int x, int y, int, void* this_);
  void showImage(const cv::Mat& img);
  void dualView(const cv::Mat& img1, const cv::Mat& img2);
  void showCamera(CameraSide cs);
  void snapshots(CameraSide cs);
  std::array<std::vector<Eigen::Vector2d>,2> pointPairs(const cv::Mat& img1, const cv::Mat& img2);

private:
  std::string window_name_;
  Camera camera_left_;
  Camera camera_right_;
  CameraInterface camera_interface_left_;
  CameraInterface camera_interface_right_;
  ImageWriter image_writer_;

  std::vector<Eigen::Vector2d> image_coordinates_l_;
  std::vector<Eigen::Vector2d> image_coordinates_r_;
  cv::RNG rng_;
  int color_counter_;
  cv::Scalar circle_color_;

};
