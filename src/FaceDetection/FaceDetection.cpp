#include "FaceDetection.hpp"
#include <opencv2/highgui/highgui.hpp>
#include <vector>
#include <iostream>

FaceDetection::FaceDetection(std::string faceConfig, std::string eyeConfig):
face_cascade_name_(faceConfig),
eyes_cascade_name_(eyeConfig)	
{
	window_name_ =  "Capture - Face detection";
        //load the cascades
   	if( !face_cascade_.load( face_cascade_name_ ) )
	{ 
		std::cout <<  "--(!)Error loading face cascade\n" << std::endl;
	}
   	if( !eyes_cascade_.load( eyes_cascade_name_ ) )
	{ 
		std::cout << "--(!)Error loading eyes cascade\n" << std::endl;
	}

}


/** @function detectAndDisplay */
void FaceDetection::detectAndDisplay( cv::Mat frame )
{
    std::vector<cv::Rect> faces;
    cv::Mat frame_gray;

    cvtColor( frame, frame_gray, cv::COLOR_BGR2GRAY );
    equalizeHist( frame_gray, frame_gray );

    //-- Detect faces
    face_cascade_.detectMultiScale( frame_gray, faces, 1.1, 2, 0|cv::CASCADE_SCALE_IMAGE, cv::Size(30, 30) );

    for ( size_t i = 0; i < faces.size(); i++ )
    {
	    cv::Point center( faces[i].x + faces[i].width/2, faces[i].y + faces[i].height/2 );
        ellipse( frame, center, cv::Size( faces[i].width/2, faces[i].height/2 ), 0, 0, 360, cv::Scalar( 255, 0, 255 ), 4, 8, 0 );

	cv::Mat faceROI = frame_gray( faces[i] );
        std::vector<cv::Rect> eyes;

        //-- In each face, detect eyes
eyes_cascade_.detectMultiScale( faceROI, eyes, 1.1, 2, 0 |cv::CASCADE_SCALE_IMAGE, cv::Size(30, 30) );

        for ( size_t j = 0; j < eyes.size(); j++ )
        {
		cv::Point eye_center( faces[i].x + eyes[j].x + eyes[j].width/2, faces[i].y + eyes[j].y + eyes[j].height/2 );
            int radius = cvRound( (eyes[j].width + eyes[j].height)*0.25 );
            circle( frame, eye_center, radius, cv::Scalar( 255, 0, 0 ), 4, 8, 0 );
        }
    }
    //-- Show what you got
    cv::imshow( window_name_, frame );
}
