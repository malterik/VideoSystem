#include "CameraInterface/CameraInterface.hpp"
#include "WindowManager/WindowManager.hpp"
#include "Utils/print.hpp"
#include "CameraMatrix/CameraMatrix.hpp"
#include "Utils/TransformationMatrix.hpp"
#include "JSONParser/JSONParser.hpp"
#include <opencv2/opencv.hpp>

int main(void)
{
  Camera cam = LOCAL_CAM;
  CameraInterface camera(cam);
  TransformationMatrix camPose("config/CameraPose.json");
  std::string windowName = "Main Window";
  camera.setResolution(1280,720);
  JSONParser jp;
  std::vector<Eigen::Vector2f> mp1 = jp.getVector("config/matchedPoints1.json");
  std::vector<Eigen::Vector2f> mp2 = jp.getVector("config/matchedPoints2.json");

  // std::cout << camPose.getMatrix() << std::endl;

  cv::namedWindow(windowName,1);
  int counter=0;
  while(1)
  {
    WindowManager::getInstance().reset();
    cv::Mat frame = camera.getImage();
    WindowManager::getInstance().addImage(frame);
    char key = (char)cv::waitKey(10);
    if( key  == 27 ) {
      break;
    } else if (key == 32) { // Hit space bar for taking a picture
      std::string path ="Images/test";
      path += std::to_string(counter);
      path += ".png";
      cv::imwrite(path, frame);
      std::cout << "Image written: " << path << std::endl;
      counter++;
    }
    cv::imshow(windowName , WindowManager::getInstance().showMultipleImages(1));
  }
}
