#pragma once

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <string>
#include "../Utils/Utils.hpp"


class CameraInterface
{
public:
  CameraInterface(Camera cameraToUse);
  const cv::Mat& getImage();
  void setResolution(int width, int height);
  void reset(Camera cameraToUse);
private:
  //Private Member
  cv::Mat image_;
  cv::VideoCapture cap_;
  unsigned int width_;
  unsigned int height_;
  Camera cam_type_;

  //Constants
  const std::string STREAM_ADDR="rtp://239.192.140.99:5004";
};
