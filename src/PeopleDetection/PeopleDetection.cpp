#include "PeopleDetection.hpp"
#include "../WindowManager/WindowManager.hpp"

PeopleDetection::PeopleDetection() {
    kernel_size_ = 4;
    p_background_subtractor_ = new cv::BackgroundSubtractorMOG();
    kernel_= cv::getStructuringElement(0,
                cv::Size(2 * kernel_size_ + 1, 2 * kernel_size_ + 1), 
                cv::Point(kernel_size_,kernel_size_)
             );

}

void PeopleDetection::detect(cv::Mat image) {
    image_=image;
    p_background_subtractor_->operator()(image,background_image_);
    morph_img_ = cv::Mat::zeros(background_image_.size(), CV_8UC1);
    cv::morphologyEx(background_image_,morph_img_, cv::MORPH_OPEN, kernel_);
    cv::morphologyEx(morph_img_, morph_img_, cv::MORPH_CLOSE, kernel_);
    cv::findContours(morph_img_, contours_, hierarchy_, 
    CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0,0));
    contours_poly.resize( contours_.size() );
    boundRect.resize( contours_.size() );
    center.resize( contours_.size() );
    radius.resize( contours_.size() );
    for( unsigned int i = 0; i < contours_.size(); i++ )
    { 
        approxPolyDP( cv::Mat(contours_[i]), contours_poly[i], 3, true );
        boundRect[i] = boundingRect( cv::Mat(contours_poly[i]) );
        minEnclosingCircle( (cv::Mat)contours_poly[i], center[i], radius[i] );
    }

}

void PeopleDetection::debugImage() {

    cv::RNG rng(12344);
    /// Draw polygonal contour + bonding rects + circles
    cv::Mat drawing = cv::Mat::zeros(morph_img_.size(), CV_8UC3 );
    for( unsigned int i = 0; i< contours_.size(); i++ )
    {
        cv::Scalar color = cv::Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
        drawContours( drawing, contours_poly, i, color, 1, 8, std::vector<cv::Vec4i>(), 0, cv::Point() );
        rectangle( drawing, boundRect[i].tl(), boundRect[i].br(), color, 2, 8, 0 );
        circle( drawing, center[i], (int)radius[i], color, 2, 8, 0 );
    }
    WindowManager::getInstance().reset();
    WindowManager::getInstance().addImage(image_);
    WindowManager::getInstance().addImage(background_image_);
    WindowManager::getInstance().addImage(morph_img_);
    WindowManager::getInstance().addImage(drawing);

}
