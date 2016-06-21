#include "Utils/DisableWarnings.hpp"
#include "PositionEstimator/PositionEstimator.hpp"
#include "ImageViewer/ImageViewer.hpp"
#include <opencv2/core/core.hpp>
#include "JSONParser/JSONParser.hpp"
#include "Utils/TransformationMatrix.hpp"
#include "Utils/print.hpp"

int main(void)
{
  CameraType camtype = IP_CAM1;
  Camera cam;
  cam.ct = camtype;
  cam.img_width = 1920;
  cam.img_height = 1080;
  ImageViewer iv("Main Window", cam);

  // cv::Mat img1 = cv::imread("/home/erik/Master/Images/P50-Home/Ball/snapshot0.png", CV_LOAD_IMAGE_COLOR);
  // cv::Mat img2 = cv::imread("/home/erik/Master/Images/P50-Home/Ball/snapshot1.png", CV_LOAD_IMAGE_COLOR);
  // PositionEstimator pe(cam, "config/CameraPose1.json", cam, "config/CameraPose2.json");
  // iv.snapshots(cam);
  // points = pe.triangulate(iv.pointPairs(img1, img2));
  iv.showCamera();
}
