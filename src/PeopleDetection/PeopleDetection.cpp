#include "PeopleDetection.hpp"
#include "../WindowManager/WindowManager.hpp"
#include "../json/json.hpp"
#include <iostream>
#include <fstream>

using json = nlohmann::json;


PeopleDetection::PeopleDetection() : 
    background_image_(), blur_img_(), contour_img_(),
    image_(), kernel_(), thresh_img_(),
    contours_(), contours_poly(), hierarchy_(),
    people_candidates_(), p_background_subtractor_(new cv::BackgroundSubtractorMOG),
    p_background_subtractor2_(new cv::BackgroundSubtractorMOG2), p_background_subtractor3_(new cv::BackgroundSubtractorGMG),
    FILE_NAME_("config/PeopleDetection.json")
{
    readConfig();
    kernel_= cv::getStructuringElement(0,
                cv::Size(2 * DILATE_KERNEL_SIZE_+ 1, 2 * DILATE_KERNEL_SIZE_+ 1), 
                cv::Point(DILATE_KERNEL_SIZE_, DILATE_KERNEL_SIZE_)
             );
    // p_background_subtractor2_->set("nmixtures",1); 

}

void PeopleDetection::reset() {

    //Reset all vectors
    people_candidates_.clear();
    contours_poly.clear();
}

// Trackbars

int dilateKernel;
int blurKernel; 
int threshold;
int minBoundingBoxArea;

void on_trackbar_dilate( int, void* )
{
    PeopleDetection peopleDetector;
    if(dilateKernel == 0) return;
    peopleDetector.writeConfig();
}

void on_trackbar_blur( int, void* )
{
    PeopleDetection peopleDetector;
    if(blurKernel == 0) return;
    peopleDetector.writeConfig();
}

void on_trackbar_threshold( int, void* )
{
    PeopleDetection peopleDetector;
    peopleDetector.writeConfig();
}

void on_trackbar_area( int, void* )
{
    PeopleDetection peopleDetector;
    peopleDetector.writeConfig();
}


void PeopleDetection::showTrackbars(const char* windowName) {

    dilateKernel = DILATE_KERNEL_SIZE_;
    blurKernel = BLUR_KERNEL_SIZE_; 
    threshold = THRESHOLD_; 
    minBoundingBoxArea = MIN_BOUNDING_BOX_AREA_; 

    cv::createTrackbar("Dilate Kernel" , windowName, &dilateKernel, 30, on_trackbar_dilate );
    cv::createTrackbar("Blur Kernel" , windowName, &blurKernel, 30, on_trackbar_blur );
    cv::createTrackbar("Threshold" , windowName, &threshold, 255, on_trackbar_threshold );
    cv::createTrackbar("minBoundingBoxArea" , windowName, &minBoundingBoxArea, 50000, on_trackbar_area );

}
const std::vector<cv::Rect>& PeopleDetection::detect(const cv::Mat& image) {

    readConfig();
    cv::HOGDescriptor hog;
    hog.setSVMDetector(cv::HOGDescriptor::getDefaultPeopleDetector());
    std::vector<cv::Point> foundLocations;
    image_=image;
    p_background_subtractor_->operator()(image,background_image_);
    // p_background_subtractor2_->operator()(image,background_image_);
    // p_background_subtractor3_->operator()(image,background_image_);
    // cv::threshold(background_image_, thresh_img_, THRESHOLD_, 255, CV_THRESH_BINARY);
    cv::blur(background_image_, blur_img_, cv::Size(2 * BLUR_KERNEL_SIZE_ + 1, 2 * BLUR_KERNEL_SIZE_ +1));
    cv::dilate(blur_img_, contour_img_,cv::getStructuringElement(0,
                                       cv::Size(2 * DILATE_KERNEL_SIZE_+ 1, 2 * DILATE_KERNEL_SIZE_+ 1), 
                                       cv::Point(DILATE_KERNEL_SIZE_, DILATE_KERNEL_SIZE_)));
    cv::findContours(contour_img_, contours_, hierarchy_, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE, cv::Point(0,0));
    contours_poly.resize( contours_.size() );
    for( unsigned int i = 0; i < contours_.size(); i++ )
    { 
        approxPolyDP( cv::Mat(contours_[i]), contours_poly[i], 3, true );
        cv::Rect boundRect = boundingRect( cv::Mat(contours_poly[i]) );
        // cv::Mat roi = image(boundRect); 
        // cv::Mat window;
        // cv::resize(roi, window, cv::Size(64,128));
        // hog.detect(window, foundLocations);
        // cv::imshow("window", window);
        // if(!foundLocations.empty()) {
        //     //is person
        //     people_candidates_.push_back(boundRect); 
        // }
        if(boundRect.area() > MIN_BOUNDING_BOX_AREA_)
        {
           people_candidates_.push_back(boundRect); 
        }
    }


    // HOG verification of bounding boxes
    return people_candidates_;
}

void PeopleDetection::debugImage() const  {

    WindowManager::getInstance().addImage(background_image_);
    WindowManager::getInstance().addImage(thresh_img_);
    WindowManager::getInstance().addImage(blur_img_);
    WindowManager::getInstance().addImage(contour_img_);
}

void PeopleDetection::writeConfig() {
    json peopleDetectionConfig; 
    std::ofstream configFile;

    peopleDetectionConfig["DILATE_KERNEL_SIZE_"] = DILATE_KERNEL_SIZE_;
    peopleDetectionConfig["BLUR_KERNEL_SIZE_"] = BLUR_KERNEL_SIZE_;
    peopleDetectionConfig["THRESHOLD_"] = THRESHOLD_;
    peopleDetectionConfig["MIN_BOUNDING_BOX_AREA_"] = MIN_BOUNDING_BOX_AREA_;
        
    configFile.open(FILE_NAME_); 
    if (configFile.is_open()) {
        configFile<< peopleDetectionConfig.dump(4) << std::endl;
        configFile.close();                    
    }
    else std::cout << "Unable to open file"; 
}

void PeopleDetection::readConfig() {
    std::string line;
    json peopleDetectionConfig; 
    std::ifstream configFile (FILE_NAME_);
    if (configFile.is_open()) {
        std::string str((std::istreambuf_iterator<char>(configFile)),
                         std::istreambuf_iterator<char>());
        peopleDetectionConfig = json::parse(str);    
        DILATE_KERNEL_SIZE_ = peopleDetectionConfig["DILATE_KERNEL_SIZE_"];
        BLUR_KERNEL_SIZE_ = peopleDetectionConfig["BLUR_KERNEL_SIZE_"];
        THRESHOLD_ = peopleDetectionConfig["THRESHOLD_"];
        MIN_BOUNDING_BOX_AREA_ = peopleDetectionConfig["MIN_BOUNDING_BOX_AREA_"];
        configFile.close();
    } else std::cout << "Unable to open people detection config file" << std::endl; 
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
        
