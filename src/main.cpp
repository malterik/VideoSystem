#include "CameraInterface/CameraInterface.hpp"
#include "FaceDetection/FaceDetection.hpp"
#include "PeopleDetection/PeopleDetection.hpp"
#include "BlobDetection/BlobDetection.hpp"
#include "WindowManager/WindowManager.hpp"

using namespace cv;


string face_cascade_name = "haarcascade_frontalface_alt.xml";
string eyes_cascade_name = "haarcascade_eye_tree_eyeglasses.xml";

int main(void)
{
    cv::RNG rng(12344);
    CameraInterface camera; 
    FaceDetection faceDetector(face_cascade_name, eyes_cascade_name);   
    PeopleDetection peopleDetector;
    BlobDetection blobDetector;

    cv::Ptr<BackgroundSubtractorMOG> pBs;
    pBs = new cv::BackgroundSubtractorMOG();

    // camera.setResolution(320,240);
    camera.setResolution(640,480);
    int kernel_size =10;
    cv::Mat kernel = cv::getStructuringElement(0,cv::Size(2*kernel_size+1,2*kernel_size+1), cv::Point(kernel_size,kernel_size));
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    while(1) 
    {
        cv::Mat frame = camera.getImage();
        cv::Mat bg;  
        pBs->operator()(frame,bg);
        cv::Mat morph_img = Mat::zeros(bg.size(), CV_8UC1);
        cv::morphologyEx(bg,morph_img, cv::MORPH_OPEN, kernel);
        cv::morphologyEx(morph_img, morph_img, cv::MORPH_CLOSE, kernel);
        cv::findContours(morph_img, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0,0));
        // faceDetector.detectAndDisplay(frame);
        // peopleDetector.detectAndDisplay(frame);
        // cv::Mat blob = blobDetector.getBlobImage(frame);
        vector<vector<Point> > contours_poly( contours.size() );
        vector<Rect> boundRect( contours.size() );
        vector<Point2f>center( contours.size() );
        vector<float>radius( contours.size() );

        for( unsigned int i = 0; i < contours.size(); i++ )
        { 
            approxPolyDP( Mat(contours[i]), contours_poly[i], 3, true );
            boundRect[i] = boundingRect( Mat(contours_poly[i]) );
            minEnclosingCircle( (Mat)contours_poly[i], center[i], radius[i] );
        }


        /// Draw polygonal contour + bonding rects + circles
        Mat drawing = Mat::zeros(morph_img.size(), CV_8UC3 );
        for( unsigned int i = 0; i< contours.size(); i++ )
        {
            Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
            drawContours( drawing, contours_poly, i, color, 1, 8, vector<Vec4i>(), 0, Point() );
            rectangle( drawing, boundRect[i].tl(), boundRect[i].br(), color, 2, 8, 0 );
            circle( drawing, center[i], (int)radius[i], color, 2, 8, 0 );
        } 
        WindowManager::getInstance().reset();
        WindowManager::getInstance().addImage(frame);
        WindowManager::getInstance().addImage(bg);
        WindowManager::getInstance().addImage(morph_img);
        WindowManager::getInstance().addImage(drawing);
        cv::imshow("Images" , WindowManager::getInstance().showMultipleImages(2)); 
        int c = waitKey(10);
        if( (char)c == 27 ) { break; } // escape
    }
}


