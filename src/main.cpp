#include "CameraInterface/CameraInterface.hpp"
#include "FaceDetection/FaceDetection.hpp"

using namespace cv;


String face_cascade_name = "haarcascade_frontalface_alt.xml";
String eyes_cascade_name = "haarcascade_eye_tree_eyeglasses.xml";

int main(void)
{
   CameraInterface camera; 
   FaceDetection faceDetector(face_cascade_name, eyes_cascade_name);   

   camera.setResolution(320,240);
   while(1) 
   {
       cv::Mat frame = camera.getImage();
       faceDetector.detectAndDisplay(frame);
       int c = waitKey(10);
       if( (char)c == 27 ) { break; } // escape
   }
}


