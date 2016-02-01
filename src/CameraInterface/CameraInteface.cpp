#include "CameraInteface.hpp"
#include <iostream>
CameraInteface::CameraInteface() : image_(), cap_(0) 
{

   if(!cap_.isOpened()) {
	std::cout << "Could not open camera"  << std::endl;
   }  
}


cv::Mat CameraInteface::getImage() 
{
	cap_ >> image_;
	return image_;	
}
