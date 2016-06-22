#include "Utils/DisableWarnings.hpp"
#include "PositionEstimator/PositionEstimator.hpp"
#include "ImageViewer/ImageViewer.hpp"
#include <opencv2/core/core.hpp>
#include "JSONParser/JSONParser.hpp"
#include "Utils/TransformationMatrix.hpp"
#include "Utils/print.hpp"

int main(void)
{
  // CameraType camtypeL = IP_CAM1;
  CameraType camtypeL = LOCAL_CAM;
  Camera camL;
  camL.ct = camtypeL;
  camL.img_width = 1920;
  camL.img_height = 1080;
  // CameraType camtypeR = LOCAL_CAM;
  CameraType camtypeR = IP_CAM2;
  Camera camR;
  camR.ct = camtypeR;
  camR.img_width = 1920;
  camR.img_height = 1080;
  // cv::VideoCapture camera2("rtp://239.192.140.12:5004");
  // cv::VideoCapture camera1("rtp://239.192.140.11:5004");
  // while(1) {
  //   char key = (char)cv::waitKey(10);
  //   cv::Mat frameR;
  //   cv::Mat frameL;
  //   camera2 >> frameR;
  //   camera1 >> frameL;
  //   if( key  == 27 ) {
  //     break;
  //   }
  //   cv::imshow("Left", frameL);
  //   cv::imshow("Right", frameR);
  // }
  ImageViewer iv("Main Window", camL, camR);

  // cv::Mat img1 = cv::imread("/home/erik/Master/Images/P50-Home/Ball/snapshot0.png", CV_LOAD_IMAGE_COLOR);
  // cv::Mat img2 = cv::imread("/home/erik/Master/Images/P50-Home/Ball/snapshot1.png", CV_LOAD_IMAGE_COLOR);
  // PositionEstimator pe(cam, "config/CameraPose1.json", cam, "config/CameraPose2.json");
  // iv.snapshots(cam);
  // points = pe.triangulate(iv.pointPairs(img1, img2));
  // iv.snapshots(LEFT_CAM);
  iv.snapshots(LEFT_CAM);
}
