#include "PeopleDetection.hpp"
#include "../WindowManager/WindowManager.hpp"

PeopleDetection::PeopleDetection() : 
    background_image_(), blur_img_(), contour_img_(),
    image_(), kernel_(), thresh_img_(),
    contours_(), contours_poly(), hierarchy_(),
    people_candidates_(), p_background_subtractor_(new cv::BackgroundSubtractorMOG),
    DILATE_KERNEL_SIZE_(7), BLUR_KERNEL_SIZE_(15), THRESHOLD_(200), MIN_BOUNDING_BOX_AREA_(10000)
{
    kernel_= cv::getStructuringElement(0,
                cv::Size(2 * DILATE_KERNEL_SIZE_+ 1, 2 * DILATE_KERNEL_SIZE_+ 1), 
                cv::Point(DILATE_KERNEL_SIZE_, DILATE_KERNEL_SIZE_)
             );

}

void PeopleDetection::reset() {

    //Reset all vectors
    people_candidates_.clear();
    contours_poly.clear();
}


const std::vector<cv::Rect>& PeopleDetection::detect(const cv::Mat& image) {

    image_=image;
    p_background_subtractor_->operator()(image,background_image_);
    cv::threshold(background_image_, thresh_img_, THRESHOLD_, 255, CV_THRESH_BINARY);
    cv::blur(thresh_img_, blur_img_, cv::Size(2 * BLUR_KERNEL_SIZE_ + 1, 2 * BLUR_KERNEL_SIZE_ +1));
    cv::dilate(blur_img_, contour_img_,cv::getStructuringElement(0,
                                       cv::Size(2 * DILATE_KERNEL_SIZE_+ 1, 2 * DILATE_KERNEL_SIZE_+ 1), 
                                       cv::Point(DILATE_KERNEL_SIZE_, DILATE_KERNEL_SIZE_)));
    cv::findContours(contour_img_, contours_, hierarchy_, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE, cv::Point(0,0));
    contours_poly.resize( contours_.size() );
    for( unsigned int i = 0; i < contours_.size(); i++ )
    { 
        approxPolyDP( cv::Mat(contours_[i]), contours_poly[i], 3, true );
        cv::Rect boundRect = boundingRect( cv::Mat(contours_poly[i]) );
        if(boundRect.area() > MIN_BOUNDING_BOX_AREA_)
        {
           people_candidates_.push_back(boundRect); 
        }
    }
    return people_candidates_;
}

void PeopleDetection::debugImage() const  {

    WindowManager::getInstance().addImage(background_image_);
    WindowManager::getInstance().addImage(thresh_img_);
    WindowManager::getInstance().addImage(blur_img_);
    WindowManager::getInstance().addImage(contour_img_);
}

// Getter and setter functions 
void PeopleDetection::setDilateKernelSize(int dilateKernelSize) {
    DILATE_KERNEL_SIZE_ = dilateKernelSize;
}
int PeopleDetection::getDilateKernelSize() {
    return DILATE_KERNEL_SIZE_;
}

void PeopleDetection::setBlurKernelSize(int blurKernelSize) {
    BLUR_KERNEL_SIZE_ = blurKernelSize;
}
int PeopleDetection::getBlurKernelSize() {
    return BLUR_KERNEL_SIZE_;
}

void PeopleDetection::setThreshold(int threshold) {
    THRESHOLD_ = threshold;
}
int PeopleDetection::getThreshold() {
    return THRESHOLD_;
}

void PeopleDetection::setMinBoundingBoxArea(int minBoundingBoxArea) {
    MIN_BOUNDING_BOX_AREA_ = minBoundingBoxArea;
}
int PeopleDetection::getMinBoundingBoxArea() {
    return MIN_BOUNDING_BOX_AREA_;
}
