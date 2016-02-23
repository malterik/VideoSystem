#include "CameraInterface/CameraInterface.hpp"
#include "WindowManager/WindowManager.hpp"
#include "PeopleDetection/PeopleDetection.hpp"
#include "json/json.hpp"

using json = nlohmann::json;

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
    peopleDetector.writeConfig();
}

void on_trackbar_blur( int, void* )
{
    if(blurKernel == 0) return;
    peopleDetector.setBlurKernelSize(blurKernel);
    peopleDetector.writeConfig();
}

void on_trackbar_threshold( int, void* )
{
    peopleDetector.setThreshold(threshold);
    peopleDetector.writeConfig();
}

void on_trackbar_area( int, void* )
{
    peopleDetector.setMinBoundingBoxArea(minBoundingBoxArea);
    peopleDetector.writeConfig();
}

int main(void)
{
    CameraInterface camera; 
    std::vector<cv::Rect> people;
                                                         
    camera.setResolution(320,240);
    // camera.setResolution(640,480);
    dilateKernel = peopleDetector.getDilateKernelSize();
    blurKernel = peopleDetector.getBlurKernelSize();
    threshold = peopleDetector.getThreshold();
    minBoundingBoxArea = peopleDetector.getMinBoundingBoxArea();

    cv::namedWindow("Images",1);
    cv::createTrackbar("Dilate Kernel" , "Images", &dilateKernel,30, on_trackbar_dilate );
    cv::createTrackbar("Blur Kernel" , "Images", &blurKernel,30, on_trackbar_blur );
    // cv::createTrackbar("Threshold" , "Images", &threshold,255, on_trackbar_threshold );
    cv::createTrackbar("minBoundingBoxArea" , "Images", &minBoundingBoxArea,50000, on_trackbar_area );

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

