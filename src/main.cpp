#include "CameraInterface/CameraInterface.hpp"
#include "WindowManager/WindowManager.hpp"
#include "PeopleDetection/PeopleDetection.hpp"
#include "json/json.hpp"
#include "Utils/print.hpp"
#include "ImageSubtractor/ImageSubtractor.hpp"
#include "CameraMatrix/CameraMatrix.hpp"
#include "Utils/TransformationMatrix.hpp"

int main(void)
{
  Camera cam = IP_CAM;
  CameraInterface camera(cam);
  PeopleDetection peopleDetector;
  CameraMatrix cm(cam);
  std::vector<cv::Rect> people;
  std::string windowName = "Main Window";

  // camera.setResolution(640,480);
  // camera.setResolution(1024,768);
  camera.setResolution(1920,1080);

  cv::namedWindow(windowName,1);
  Eigen::Vector2i poi2(960,540);
  Eigen::Vector3d poi = cm.pixel2world(poi2);
  Eigen::Vector3d pixelPoint2 = cm.pixel2world(poi2);
  std::cout << "Pixel Point: " << std::endl << poi <<  std::endl;
  std::cout << "Pixel Point2: " << std::endl << pixelPoint2 <<  std::endl;
  // peopleDetector.showTrackbars(windowName.c_str());
  cv::Mat img1, img2, diffImg, test;
  cv::Mat frame(camera.getImage());
  ImageSubtractor imageSubtractor(frame);
  int counter=0;
  while(1)
  {
    WindowManager::getInstance().reset();
    // peopleDetector.reset();
    frame = camera.getImage();
    cv::circle(frame,cv::Point(pixelPoint2(0),pixelPoint2(1)), 5 , cv::Scalar(0,0,255));
    WindowManager::getInstance().addImage(frame);
    // people = peopleDetector.detect(frame);
    // peopleDetector.debugImage();

    // WindowManager::getInstance().drawBoundingBox(people,frame);

    char key = (char)cv::waitKey(10);
    if( key  == 27 ) {
      break;
    } else if (key == 32) { // Hit space bar for resetting the background
       // imageSubtractor.setBackground(frame);
      std::string path ="Images/test";
      path += std::to_string(counter);
      path += ".png";
      cv::imwrite(path, frame);
      std::cout << "Image written: " << path << std::endl;
      counter++;
    }

    // imageSubtractor.subtractBackground(frame);
    // cv::Mat bg = imageSubtractor.getDiffImage();
    // cv::cvtColor(bg,bg,CV_BGR2GRAY);
    // cv::threshold(bg,bg,20,255, CV_THRESH_BINARY);
    // WindowManager::getInstance().addImage(imageSubtractor.getBackground());
    // WindowManager::getInstance().addImage(bg);
    // WindowManager::getInstance().addImage(imageSubtractor.getDiffImage());
    cv::imshow(windowName , WindowManager::getInstance().showMultipleImages(1));
  }
}
