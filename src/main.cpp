#include "CameraInterface/CameraInterface.hpp"
#include "FaceDetection/FaceDetection.hpp"
#include "PeopleDetectionHOG/PeopleDetectionHOG.hpp"
#include "BlobDetection/BlobDetection.hpp"
#include "WindowManager/WindowManager.hpp"
#include "PeopleDetection/PeopleDetection.hpp"



cv::string face_cascade_name = "haarcascade_frontalface_alt.xml";
cv::string eyes_cascade_name = "haarcascade_eye_tree_eyeglasses.xml";

int main(void)
{
    CameraInterface camera; 
    FaceDetection faceDetector(face_cascade_name, eyes_cascade_name);   
    BlobDetection blobDetector;
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
        int c = cv::waitKey(10);
        if( (char)c == 27 ) { break; } // escape
    }
}


