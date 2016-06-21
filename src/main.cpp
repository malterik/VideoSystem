#include "Utils/DisableWarnings.hpp"
#include "PositionEstimator/PositionEstimator.hpp"
#include "ImageViewer/ImageViewer.hpp"
#include <opencv2/core/core.hpp>
#include "JSONParser/JSONParser.hpp"
#include "Utils/TransformationMatrix.hpp"
#include "Utils/print.hpp"

int main(void)
{
  CameraType camtypeL = IP_CAM1;
  Camera camL;
  camL.ct = camtypeL;
  camL.img_width = 640;
  camL.img_height = 480;
  CameraType camtypeR = IP_CAM2;
  Camera camR;
  camR.ct = camtypeR;
  camR.img_width = 640;
  camR.img_height = 480;
  CameraInterface left(IP_CAM1);
  // CameraInterface right(IP_CAM1);
  left.setResolution(640,480);
  // right.setResolution(640,480);
  cv::namedWindow("Left",1);
  cv::namedWindow("Right",1);
  while(1) {
    char key = (char)cv::waitKey(10);
    cv::Mat frameL = left.getImage();
    // cv::Mat frameR = right.getImage();
    if( key  == 27 ) {
      break;
    }
    // cv::imshow("Right", frameR);
    cv::imshow("Left", frameL);
  }
  // ImageViewer iv("Main Window", camL, camR);

  // cv::Mat img1 = cv::imread("/home/erik/Master/Images/P50-Home/Ball/snapshot0.png", CV_LOAD_IMAGE_COLOR);
  // cv::Mat img2 = cv::imread("/home/erik/Master/Images/P50-Home/Ball/snapshot1.png", CV_LOAD_IMAGE_COLOR);
  // PositionEstimator pe(cam, "config/CameraPose1.json", cam, "config/CameraPose2.json");
  // iv.snapshots(cam);
  // points = pe.triangulate(iv.pointPairs(img1, img2));
  // iv.snapshots(BOTH);
}
