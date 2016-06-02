#include "CameraInterface/CameraInterface.hpp"
#include "WindowManager/WindowManager.hpp"
#include "Utils/print.hpp"
#include "CameraMatrix/CameraMatrix.hpp"
#include "Utils/TransformationMatrix.hpp"
#include "JSONParser/JSONParser.hpp"
#include "PositionEstimator/PositionEstimator.hpp"
#include "ImageWriter/ImageWriter.hpp"

int main(void)
{
  Camera cam = LOCAL_CAM;
  CameraInterface camera(cam);
  CameraMatrix leftCam(cam, "config/CameraPose1.json");
  CameraMatrix rightCam(cam, "config/CameraPose2.json");
  PositionEstimator pe(leftCam, rightCam);
  std::string windowName = "Main Window";
  camera.setResolution(1280,720);
  ImageWriter iw("Images/");

  std::vector<Eigen::Vector2d> mp1 = JSONParser::getInstance().getVector("config/matchedPoints1.json");
  std::vector<Eigen::Vector2d> mp2 = JSONParser::getInstance().getVector("config/matchedPoints2.json");
  pe.triangulate(mp1,mp2);

  cv::namedWindow(windowName,1);
  while(1)
  {
    WindowManager::getInstance().reset();
    cv::Mat frame = camera.getImage();
    WindowManager::getInstance().addImage(frame);
    char key = (char)cv::waitKey(10);
    if( key  == 27 ) {
      break;
    } else if (key == 32) { // Hit space bar for taking a picture
      iw.writeImage(frame, "test");
    }
    cv::imshow(windowName , WindowManager::getInstance().showMultipleImages(1));
  }
}
