#include "PeopleDetection.hpp"

PeopleDetection::PeopleDetection() {
    hog_.setSVMDetector(cv::HOGDescriptor::getDefaultPeopleDetector());	
}

void PeopleDetection::detectAndDisplay(cv::Mat image) {

    hog_.detectMultiScale(image, found_, 0, cv::Size(8,8), cv::Size(32,32), 1.05, 2);
    unsigned int i,j;	
    for (i = 0; i < found_.size(); i++) {
        cv::Rect r = found_[i];	
        for (j = 0; j < found_.size(); j++) {
            if (j!=i && (r & found_[j])==r) {
                break;	
	    }
	    if (j==found_.size()) {
	        found_filtered_.push_back(r);		
	    }
					
        }	
    }
    for (i = 0; i < found_filtered_.size(); i++) {
        cv::Rect r = found_filtered_[i];
        r.x += cvRound(r.width*0.1);
	r.width = cvRound(r.width*0.8);
	r.y += cvRound(r.height*0.06);
	r.height = cvRound(r.height*0.9);
	cv::rectangle(image,r.tl(),r.br(),cv::Scalar(0,255,0),2);
		
    }
    std::cout << "size of found " << found_.size() << std::endl;
    std::cout << "size of found filtered" << found_filtered_.size() << std::endl;
    cv::imshow("PeopleDetection",image);
}
