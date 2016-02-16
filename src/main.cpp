#include "CameraInterface/CameraInterface.hpp"
#include "FaceDetection/FaceDetection.hpp"
#include "PeopleDetectionHOG/PeopleDetectionHOG.hpp"
#include "BlobDetection/BlobDetection.hpp"
#include "WindowManager/WindowManager.hpp"
#include "PeopleDetection/PeopleDetection.hpp"

using namespace cv;


string face_cascade_name = "haarcascade_frontalface_alt.xml";
string eyes_cascade_name = "haarcascade_eye_tree_eyeglasses.xml";

int main(void)
{
    CameraInterface camera; 
    FaceDetection faceDetector(face_cascade_name, eyes_cascade_name);   
    BlobDetection blobDetector;
    PeopleDetection peopleDetector;

    camera.setResolution(320,240);
    // camera.setResolution(640,480);
    while(1) 
    {
        cv::Mat frame = camera.getImage();
        peopleDetector.detect(frame);
        peopleDetector.debugImage();
        cv::imshow("Images" , WindowManager::getInstance().showMultipleImages(2)); 
        int c = waitKey(10);
        if( (char)c == 27 ) { break; } // escape
    }
}


