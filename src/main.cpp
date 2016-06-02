#include "CameraInterface/CameraInterface.hpp"
#include "WindowManager/WindowManager.hpp"
#include "Utils/print.hpp"
#include "CameraMatrix/CameraMatrix.hpp"
#include "Utils/TransformationMatrix.hpp"
#include "JSONParser/JSONParser.hpp"
#include "PositionEstimator/PositionEstimator.hpp"
#include "ImageWriter/ImageWriter.hpp"
#include "ImageViewer/ImageViewer.hpp"

int main(void)
{
  Camera cam = LOCAL_CAM;
  CameraInterface camera(cam);
  CameraMatrix leftCam(cam, "config/CameraPose1.json");
  CameraMatrix rightCam(cam, "config/CameraPose2.json");
  PositionEstimator pe(leftCam, rightCam);
  std::string windowName = "Main Window";
  // camera.setResolution(1280,720);
  ImageViewer iv("Main Window");

  std::vector<Eigen::Vector2d> mp1 = JSONParser::getInstance().getVector("config/matchedPoints1.json");
  std::vector<Eigen::Vector2d> mp2 = JSONParser::getInstance().getVector("config/matchedPoints2.json");
  pe.triangulate(mp1,mp2);

  cv::Mat frame;
  cv::Mat frame2;
  camera.getImage().copyTo(frame);
  camera.getImage().copyTo(frame2);
  iv.dualView(frame, frame2);
}
