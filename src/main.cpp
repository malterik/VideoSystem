#include "CameraInterface/CameraInterface.hpp"
#include "WindowManager/WindowManager.hpp"
#include "PeopleDetection/PeopleDetection.hpp"
#include "json/json.hpp"
#include "Utils/print.hpp"
#include "ImageSubtractor/ImageSubtractor.hpp"

int main(void)
{
    CameraInterface camera; 
    PeopleDetection peopleDetector;
    std::vector<cv::Rect> people;
    std::string windowName = "Main Window";

    // camera.setResolution(320,240);
    camera.setResolution(640,480);

    cv::namedWindow(windowName,1);
    
    // peopleDetector.showTrackbars(windowName.c_str());    
    cv::Mat img1, img2, diffImg, test;
    cv::Mat frame(camera.getImage());
    ImageSubtractor imageSubtractor(frame);
    while(1) 
    {
        WindowManager::getInstance().reset();
        // peopleDetector.reset();
        frame = camera.getImage();
        WindowManager::getInstance().addImage(frame);
        // people = peopleDetector.detect(frame);
        // peopleDetector.debugImage();
         
        // WindowManager::getInstance().drawBoundingBox(people,frame);
          
        char key = (char)cv::waitKey(10);
        if( key  == 27 ) {
            break;  
        } else if (key == 32) {
           imageSubtractor.setBackground(frame);
        } else if (key == 10) { 
        } 

        imageSubtractor.subtractBackground(frame);
        cv::Mat bg = imageSubtractor.getDiffImage();
        cv::cvtColor(bg,bg,CV_BGR2GRAY);
        cv::threshold(bg,bg,20,255, CV_THRESH_BINARY);
        WindowManager::getInstance().addImage(imageSubtractor.getBackground());
        WindowManager::getInstance().addImage(bg);
        // WindowManager::getInstance().addImage(imageSubtractor.getDiffImage());

        cv::imshow(windowName , WindowManager::getInstance().showMultipleImages(2)); 
    }
}

