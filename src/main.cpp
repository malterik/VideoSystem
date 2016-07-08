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

int main(void)
{
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

  StereoInterface si(camL, camR);
  cv::Mat initFrame = si.getLeftImage();
  ImageSubtractor is(initFrame);

  while(1) {
    WindowManager::getInstance().reset();
    cv::Mat leftFrame = si.getLeftImage();
    cv::Mat rightFrame = si.getRightImage();

    WindowManager::getInstance().addImage(leftFrame);
    WindowManager::getInstance().addImage(rightFrame);
    char key = (char)cv::waitKey(10);
    if( key  == 27 ) {
      break;
    } else if( key == 32 ) {
      is.setBackground(leftFrame);
    }
    cv::imshow("Window1" , WindowManager::getInstance().showMultipleImages(2) );
  }
  cv::waitKey(0);
}
