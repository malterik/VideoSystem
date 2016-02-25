#include "CameraInterface/CameraInterface.hpp"
#include "WindowManager/WindowManager.hpp"
#include "PeopleDetection/PeopleDetection.hpp"
#include "json/json.hpp"
#include "Utils/print.hpp"

int main(void)
{
    CameraInterface camera; 
    PeopleDetection peopleDetector;
    std::vector<cv::Rect> people;
    std::string windowName = "Main Window";

    camera.setResolution(320,240);
    // camera.setResolution(640,480);

    cv::namedWindow(windowName,1);
    
    peopleDetector.showTrackbars(windowName.c_str());    

    while(1) 
    {
        WindowManager::getInstance().reset();
        peopleDetector.reset();
        cv::Mat frame(camera.getImage());
        WindowManager::getInstance().addImage(frame);
        
        people = peopleDetector.detect(frame);
        peopleDetector.debugImage();
         
        WindowManager::getInstance().drawBoundingBox(people,frame);
          
        cv::imshow(windowName , WindowManager::getInstance().showMultipleImages(2)); 

        if( (char)cv::waitKey(10) == 27 )  break;  
    }
}

