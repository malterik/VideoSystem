#include "PeopleDetection.hpp"
#include "../WindowManager/WindowManager.hpp"

PeopleDetection::PeopleDetection() {
    kernel_size_ = 7;
    p_background_subtractor_ = new cv::BackgroundSubtractorMOG();
    kernel_= cv::getStructuringElement(0,
                cv::Size(2 * kernel_size_ + 1, 2 * kernel_size_ + 1), 
                cv::Point(kernel_size_,kernel_size_)
             );

}

void PeopleDetection::detect(cv::Mat image) {
    contours_poly.clear();
    boundRect.clear();
    center.clear();
    radius.clear();
    people_candidates_.clear();
    contours_poly_candidates_.clear();
    image_=image;
    p_background_subtractor_->operator()(image,background_image_);
    cv::threshold(background_image_,thresh_img_,200,255,CV_THRESH_BINARY);
    cv::blur(thresh_img_,blur_img_,cv::Size(15,15));
    cv::dilate(blur_img_,contour_img_,kernel_);
    cv::findContours(contour_img_, contours_, hierarchy_, 
        CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE, cv::Point(0,0));
    // morph_img_ = cv::Mat::zeros(background_image_.size(), CV_8UC1);
    // cv::morphologyEx(background_image_,morph_img_, cv::MORPH_OPEN, kernel_);
    // cv::morphologyEx(morph_img_, morph_img_, cv::MORPH_CLOSE, kernel_);
    // cv::findContours(background_image_, contours_, hierarchy_, 
    // CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0,0));
    contours_poly.resize( contours_.size() );
    boundRect.resize( contours_.size() );
    center.resize( contours_.size() );
    radius.resize( contours_.size() );
    people_candidates_.resize( contours_.size());
    contours_poly_candidates_.resize(contours_poly.size());
    for( unsigned int i = 0; i < contours_.size(); i++ )
    { 
        
        approxPolyDP( cv::Mat(contours_[i]), contours_poly[i], 3, true );
        boundRect[i] = boundingRect( cv::Mat(contours_poly[i]) );
        minEnclosingCircle( (cv::Mat)contours_poly[i], center[i], radius[i] );
        if(boundRect[i].area() > 10000)
        {
           std::cout << boundRect[i].area() << std::endl;
           people_candidates_.push_back(boundRect[i]); 
           contours_poly_candidates_.push_back(contours_poly[i]);
        }
    }

}

void PeopleDetection::debugImage() {

    cv::RNG rng(12344);
    /// Draw polygonal contour + bonding rects + circles
    cv::Mat drawing = cv::Mat::zeros(background_image_.size(), CV_8UC3 );
    for( unsigned int i = 0; i< people_candidates_.size(); i++ )
    {
        cv::Scalar color = cv::Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
        drawContours(image_, contours_poly_candidates_, i, color, 1, 8, std::vector<cv::Vec4i>(), 0, cv::Point() );
        rectangle(image_, people_candidates_[i].tl(), people_candidates_[i].br(), color, 2, 8, 0 );
        // circle( drawing, center[i], (int)radius[i], color, 2, 8, 0 );
    }
    WindowManager::getInstance().reset();
    WindowManager::getInstance().addImage(image_);
    WindowManager::getInstance().addImage(background_image_);
    WindowManager::getInstance().addImage(thresh_img_);
    WindowManager::getInstance().addImage(blur_img_);
    WindowManager::getInstance().addImage(contour_img_);
    // WindowManager::getInstance().addImage(drawing);

}
