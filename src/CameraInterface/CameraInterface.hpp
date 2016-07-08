#pragma once

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <string>
#include "../Utils/Utils.hpp"


class CameraInterface
{
public:
  CameraInterface(CameraType cameraToUse);
  const cv::Mat& getImage();
  void setResolution(int width, int height);
  void reset(CameraType cameraToUse);
private:
  //Private Member
  cv::Mat image_;
  cv::VideoCapture cap_;
  unsigned int width_;
  unsigned int height_;
  CameraType cam_type_;

  //Constants
  const std::string STREAM_ADDR1="rtp://239.192.140.11:5004";
  const std::string STREAM_ADDR2="rtp://239.192.140.12:5004";
  const std::string DLINK_STREAM_ADDR="rtsp://admin:@192.168.0.20:554/live1.sdp";
  const std::string DLINK_STREAM_ADDR_2="rtsp://admin:@192.168.0.22:554/live1.sdp";
  const std::string DLINK_STREAM_ADDR_HTTP="http://admin:@192.168.0.20:80/video1.mjpg";
};
