#include "PositionEstimator/PositionEstimator.hpp"
#include "ImageViewer/ImageViewer.hpp"
#include <opencv2/core/core.hpp>
#include "JSONParser/JSONParser.hpp"
#include "Utils/TransformationMatrix.hpp"
#include "Utils/print.hpp"

int main(void)
{
  std::vector<Eigen::Vector3d> points;
  Camera cam = LOCAL_CAM;
  ImageViewer iv("Main Window");

  cv::Mat img1 = cv::imread("/home/erik/Master/Images/P50-Home/Ball/snapshot0.png", CV_LOAD_IMAGE_COLOR);
  cv::Mat img2 = cv::imread("/home/erik/Master/Images/P50-Home/Ball/snapshot1.png", CV_LOAD_IMAGE_COLOR);
  print(LogLevel::DEBUG, "DEBUG");
  PositionEstimator pe(cam, "config/CameraPose1.json", cam, "config/CameraPose2.json");
  // iv.snapshots(cam);
  points = pe.triangulate(iv.pointPairs(img1, img2));
}
