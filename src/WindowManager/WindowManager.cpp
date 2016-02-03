#include "WindowManager.hpp"

WindowManager::WindowManager() {
    
}

void WindowManager::addImage(cv::Mat image) {
    img_vector_.push_back(image); 
}

void WindowManager::addImage(std::vector<cv::Mat> imageVector) {
   img_vector_.insert(img_vector_.end(), imageVector.begin(),imageVector.end()); 
}
