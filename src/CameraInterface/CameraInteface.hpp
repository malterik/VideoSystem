#pragma once

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

class CameraInteface 
{
public:
	CameraInteface();
	cv::Mat getImage();
private:
	cv::Mat image_;
	cv::VideoCapture cap_; 
};
