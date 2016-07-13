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

  localCam.setResolution(camLocal.img_width, camLocal.img_height);

  // cv::Mat initFrame = localCam.getImage();
  PeopleDetection pdL(si.getLeftImage());
  PeopleDetection pdR(si.getRightImage());
  std::vector<cv::Rect> peopleL, peopleR;

  namedWindow(trackBarWindow, cv::WINDOW_AUTOSIZE );
  pdR.showTrackbars(trackBarWindow.c_str());

  while(1) {
    WindowManager::getInstance().reset();
    pdL.reset();
    pdR.reset();
    cv::Mat frameL = si.getLeftImage();
    cv::Mat frameR = si.getRightImage();
    peopleL = pdL.detect(frameL);
    peopleR = pdR.detect(frameR);
    pdL.debugImage();
    pdR.debugImage();

    // WindowManager::getInstance().addImage(frameL);
    // WindowManager::getInstance().addImage(frameR);
    WindowManager::getInstance().drawBoundingBox(peopleL,frameL);
    WindowManager::getInstance().drawBoundingBox(peopleR,frameR);

    char key = (char)cv::waitKey(10);
    if( key  == 27 ) {
      break;
    } else if( key == 32 ) {
    }
    cv::imshow("Window1" , WindowManager::getInstance().showMultipleImages(2) );
  }
  cv::waitKey(0);
}
