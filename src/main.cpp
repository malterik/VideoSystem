#include "Utils/DisableWarnings.hpp"
#include "PositionEstimator/PositionEstimator.hpp"
#include "ImageViewer/ImageViewer.hpp"
#include <opencv2/core/core.hpp>
#include "Utils/print.hpp"
#include "ImageViewer/ImageViewer.hpp"
#include "CameraInterface/StereoInterface.hpp"

int main(void)
{
  std::string MapWindow="Window";
  CameraType camtypeL = DLINK_CAM_1;
  Camera camL;
  camL.ct = camtypeL;
  camL.img_width = 640;
  camL.img_height = 480;
  CameraType camtypeR = DLINK_CAM_2;
  Camera camR;
  camR.ct = camtypeR;
  camR.img_width = 640;
  camR.img_height = 480;
  CameraType camtypeLocal = LOCAL_CAM;
  Camera camLocal;
  camLocal.ct = camtypeLocal;
  camLocal.img_width = 640;
  camLocal.img_height = 480;

  ImageViewer iv("Main", camL, camR);
  PositionEstimator pe(camtypeL, "config/CameraPose1.json", camtypeR, "config/CameraPose2.json");

  cv::Mat imgL = cv::imread("/home/erik/Master/Matlab/Images/cameraLeft0.png");
  cv::Mat imgR = cv::imread("/home/erik/Master/Matlab/Images/cameraRight0.png");
  iv.pointPairs(imgL,imgR, pe);

}
