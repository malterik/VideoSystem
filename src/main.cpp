#include "CameraInterface/CameraInterface.hpp"
#include "WindowManager/WindowManager.hpp"
#include "PeopleDetection/PeopleDetection.hpp"
#include "json/json.hpp"
#include "Utils/print.hpp"
#include "ImageSubtractor/ImageSubtractor.hpp"
#include "CameraMatrix/CameraMatrix.hpp"

int main(void)
{
    CameraInterface camera; 
    PeopleDetection peopleDetector;
    CameraMatrix cm;
    std::vector<cv::Rect> people;
    std::string windowName = "Main Window";

    // camera.setResolution(320,240);
    camera.setResolution(640,480);
    // camera.setResolution(1024,768);

    cv::namedWindow(windowName,1);
    Eigen::Vector3d poi(0.2,0,0.2);    
    Eigen::Vector2i poi2(320,240);    
    Eigen::Vector2i pixelPoint = cm.world2pixel(poi);
    // Eigen::Vector3d pixelPoint2 = cm.pixel2world(poi2);
    std::cout << pixelPoint << std::endl;
    // std::cout << pixelPoint2 << std::endl;
    // peopleDetector.showTrackbars(windowName.c_str());    
    cv::Mat img1, img2, diffImg, test;
    cv::Mat frame(camera.getImage());
    ImageSubtractor imageSubtractor(frame);
    while(1) 
    {
        WindowManager::getInstance().reset();
        // peopleDetector.reset();
        frame = camera.getImage();
        cv::circle(frame,cv::Point(pixelPoint(0),pixelPoint(1)), 5 , cv::Scalar(0,0,255));
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
        // WindowManager::getInstance().addImage(imageSubtractor.getBackground());
        // WindowManager::getInstance().addImage(bg);
        // WindowManager::getInstance().addImage(imageSubtractor.getDiffImage());

        cv::imshow(windowName , WindowManager::getInstance().showMultipleImages(1)); 
    }
}

