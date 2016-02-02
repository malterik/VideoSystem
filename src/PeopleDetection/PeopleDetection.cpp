#include "PeopleDetection.hpp"

PeopleDetection::PeopleDetection() {
	hog_.setSVMDetector(cv::HOGDescriptor::getDefaultPeopleDetector());	
}

void PeopleDetection::detectAndDisplay(cv::Mat image) {

	hog_.detectMultiScale(image, found_, 0, cv::Size(8,8), cv::Size(32,32), 1.05, 2);
	while(1) 
	{
		unsigned int i,j;	
		for (i = 0; i < found_.size(); i++) {
			cv::Rect r = found_[i];	
			for (j = 0; j < found_.size(); j++) {
					
			}
		}
	}
}
