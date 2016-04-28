#pragma once

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <string>

enum camera {
  IP_CAM,
  LOCAL_CAM

};

class CameraInterface
{
public:
        CameraInterface(camera cameraToUse);
        const cv::Mat& getImage();
        void setResolution(int width, int height);
private:
        //Private Member
        cv::Mat image_;
        cv::VideoCapture cap_;
        unsigned int width_;
        unsigned int height_;
        camera cam_type_;

        //Constants
        const std::string STREAM_ADDR="rtp://239.192.140.99:5004";
};
