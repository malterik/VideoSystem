#include "Utils/DisableWarnings.hpp"
#include "PositionEstimator/PositionEstimator.hpp"
#include "ImageViewer/ImageViewer.hpp"
#include <opencv2/core/core.hpp>
#include "JSONParser/JSONParser.hpp"
#include "Utils/TransformationMatrix.hpp"
#include "Utils/print.hpp"
#include "CameraInterface/StereoInterface.hpp"
#include "WindowManager/WindowManager.hpp"
#include "ImageSubtractor/ImageSubtractor.hpp"
#include "PeopleDetection/PeopleDetection.hpp"
#include "StereoMatcher/StereoMatcher.hpp"
#include "ImageWriter/ImageWriter.hpp"
#include "PositionEstimator/PositionEstimator.hpp"
#include "Visualizer/Visualizer.hpp"

int main(void)
{
  std::string trackBarWindow="Window";
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

  CameraInterface localCam(camLocal.ct);
  StereoInterface si(camL,camR);
  StereoMatcher sm;
  ImageWriter iw("Images/");

  localCam.setResolution(camLocal.img_width, camLocal.img_height);

  // cv::Mat initFrame = localCam.getImage();
  PeopleDetection pdL(si.getLeftImage());
  PeopleDetection pdR(si.getRightImage());
  std::vector<cv::Rect> peopleL, peopleR;
  std::vector<std::vector<cv::Point>> matched_points;
  PositionEstimator pe(camtypeL, "config/CameraPose1.json", camtypeR, "config/CameraPose2.json");
  Visualizer v;

  namedWindow(trackBarWindow, cv::WINDOW_AUTOSIZE );
  // pdR.showTrackbars(trackBarWindow.c_str());

  while(1) {
    WindowManager::getInstance().reset();
    pdL.reset();
    pdR.reset();
    cv::Mat frameL = si.getLeftImage();
    cv::Mat frameR = si.getRightImage();
    cv::Mat pointsLeft,pointsRight;
    peopleL = pdL.detect(frameL);
    peopleR = pdR.detect(frameR);
    matched_points = sm.findPointPairs(peopleL, peopleR);
    std::vector<Eigen::Vector3d> points = pe.triangulate(matched_points);
    cv::imshow(trackBarWindow,v.showMap(points));

    WindowManager::getInstance().drawBoundingBox(peopleL, frameL);
    WindowManager::getInstance().drawBoundingBox(peopleR, frameR);
    // WindowManager::getInstance().drawPointsStereo(matched_points, frameL, frameR, pointsLeft, pointsRight);

    char key = (char)cv::waitKey(10);
    if( key  == 27 ) {
      break;
    } else if( key == 32 ) {
      iw.writeImage(pointsLeft,"LeftPoint");
      iw.writeImage(pointsRight,"RightPoint");
    } else if(key == 10) {
      print(LogLevel::INFO,"Set new background");
      pdL.setBackground(frameL);
      pdR.setBackground(frameR);
    }
    cv::imshow("Window1" , WindowManager::getInstance().showMultipleImages(2) );
  }
  cv::waitKey(0);
}
