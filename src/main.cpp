#include "PositionEstimator/PositionEstimator.hpp"
#include "ImageViewer/ImageViewer.hpp"
#include <opencv2/core/core.hpp>
#include "JSONParser/JSONParser.hpp"
#include "Utils/TransformationMatrix.hpp"
#include "Utils/print.hpp"

int main(void)
{
  Camera cam = LOCAL_CAM;
  ImageViewer iv("Main Window");

  cv::Mat img1 = cv::imread("/home/erik/Master/Images/P50-Office/test0.png", CV_LOAD_IMAGE_COLOR);
  cv::Mat img2 = cv::imread("/home/erik/Master/Images/P50-Office/test1.png", CV_LOAD_IMAGE_COLOR);
  print(LogLevel::DEBUG, "DEBUG");
  PositionEstimator pe(cam, "config/CameraPose1.json", cam, "config/CameraPose2.json");

  pe.triangulate(iv.pointPairs(img1, img2));
  std::cout << "Left Camera Matrix : " << std::endl << pe.getCameraMatrix(LEFT).getCameraMatrix()  << std::endl;
  std::cout << std::endl << std::endl;
  std::cout << "Right Camera Matrix : " << std::endl << pe.getCameraMatrix(RIGHT).getCameraMatrix()  << std::endl;
}
