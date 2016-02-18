#include "CameraInterface/CameraInterface.hpp"
#include "WindowManager/WindowManager.hpp"
#include "PeopleDetection/PeopleDetection.hpp"

const int alpha_slider_max = 100;
int dilateKernel;
int blurKernel; 
int threshold;
int minBoundingBoxArea;
PeopleDetection peopleDetector;


void on_trackbar_dilate( int, void* )
{
    if(dilateKernel == 0) return;
    peopleDetector.setDilateKernelSize(dilateKernel);
}

void on_trackbar_blur( int, void* )
{
    if(blurKernel == 0) return;
    peopleDetector.setBlurKernelSize(blurKernel);
}

void on_trackbar_threshold( int, void* )
{
    peopleDetector.setThreshold(threshold);
}

void on_trackbar_area( int, void* )
{
    peopleDetector.setMinBoundingBoxArea(minBoundingBoxArea);
}
void on_button( int, void* )
{
    peopleDetector.setMinBoundingBoxArea(minBoundingBoxArea);
}

int main(void)
{
    CameraInterface camera; 
    std::vector<cv::Rect> people;
    
    camera.setResolution(320,240);
    // camera.setResolution(640,480);
    cv::namedWindow("Images",1);
    cv::createTrackbar("Dilate Kernel" , "Images", &dilateKernel,15, on_trackbar_dilate );
    cv::createTrackbar("Blur Kernel" , "Images", &blurKernel,15, on_trackbar_blur );
    cv::createTrackbar("Threshold" , "Images", &threshold,255, on_trackbar_threshold );
    cv::createTrackbar("minBoundingBoxArea" , "Images", &minBoundingBoxArea,50000, on_trackbar_area );
    cv::createButton("Button",on_button);
    while(1) 
    {
        WindowManager::getInstance().reset();
        peopleDetector.reset();
        cv::Mat frame(camera.getImage());
        WindowManager::getInstance().addImage(frame);
        
        people = peopleDetector.detect(frame);
        peopleDetector.debugImage();
        
        WindowManager::getInstance().drawBoundingBox(people,frame);

        cv::imshow("Images" , WindowManager::getInstance().showMultipleImages(2)); 

        if( (char)cv::waitKey(10) == 27 )  break;  
    }
}


