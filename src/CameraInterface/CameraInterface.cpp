#include "CameraInterface.hpp"
#include <iostream>
CameraInterface::CameraInterface() : image_(), cap_(0) 
{

   if(!cap_.isOpened()) {
	std::cout << "Could not open camera"  << std::endl;
   }  
}


cv::Mat CameraInterface::getImage() 
{
	cap_ >> image_;
	return image_;	
	
}
void CameraInterface::setResolution(int width, int height)
{
	cap_.set(CV_CAP_PROP_FRAME_WIDTH, width);
	cap_.set(CV_CAP_PROP_FRAME_HEIGHT, height);
}
