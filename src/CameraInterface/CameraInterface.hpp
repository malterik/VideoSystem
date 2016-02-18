#pragma once

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

class CameraInterface 
{
public:
	CameraInterface();
	const cv::Mat& getImage();
	void setResolution(int width, int height);
private:
	cv::Mat image_;
	cv::VideoCapture cap_; 
};
