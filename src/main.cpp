#include "CameraInterface/CameraInterface.hpp"
#include "WindowManager/WindowManager.hpp"
#include "PeopleDetection/PeopleDetection.hpp"

int main(void)
{
    CameraInterface camera; 
    PeopleDetection peopleDetector;
    std::vector<cv::Rect> people;
    
    // camera.setResolution(320,240);
    camera.setResolution(640,480);

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


