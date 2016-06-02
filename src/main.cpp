#include "PositionEstimator/PositionEstimator.hpp"
#include "ImageViewer/ImageViewer.hpp"
#include <opencv2/core/core.hpp>

int main(void)
{
  Camera cam = LOCAL_CAM;
  PositionEstimator pe(cam, "config/CameraPose1.json", cam, "config/CameraPose2.json");
  ImageViewer iv("Main Window");

  cv::Mat img1 = cv::imread("Images/snapshot0.png", CV_LOAD_IMAGE_COLOR);
  cv::Mat img2 = cv::imread("Images/snapshot1.png", CV_LOAD_IMAGE_COLOR);

  pe.triangulate(iv.pointPairs(img1, img2));

}
