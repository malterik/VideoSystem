#include "PositionEstimator.hpp"
#include <opencv2/opencv.hpp>
#include "../Utils/print.hpp"

PositionEstimator::PositionEstimator(const CameraMatrix& leftCameraMatrix, const CameraMatrix& rightCameraMatrix) :
  left_camera_matrix_(leftCameraMatrix),
  right_camera_matrix_(rightCameraMatrix)
{
}

void PositionEstimator::triangulate(const std::vector<Eigen::Vector2d>& matchedPoints1, const std::vector<Eigen::Vector2d>& matchedPoints2) {

  if(matchedPoints1.size() != matchedPoints2.size()) {
     print(LogLevel::ERROR, "Number of points does not match!");
     return;
  }
  // int N = matchedPoints1.size();
  int N = 2;

  cv::Mat mp1(1,N,CV_64FC2);
  cv::Mat mp2(1,N,CV_64FC2);
  cv::Mat result;
  cv::Mat lCam(3,4,CV_64FC1);
  cv::Mat rCam(3,4,CV_64FC1);

  for(int x = 0; x < 3; x++) {
    for(int y = 0; y < 4; y++) {
      lCam.at<double>(x,y) = left_camera_matrix_.getCameraMatrix()(x,y);
      rCam.at<double>(x,y) = right_camera_matrix_.getCameraMatrix()(x,y);
    }
  }

  for (int i = 0; i < N; i++) {
    mp1.at<cv::Vec2d>(0,i)[0] = matchedPoints1[i][0];
    mp1.at<cv::Vec2d>(0,i)[1] = matchedPoints1[i][1];

    mp2.at<cv::Vec2d>(0,i)[0] = matchedPoints2[i][0];
    mp2.at<cv::Vec2d>(0,i)[1] = matchedPoints2[i][1];
  }

  cv::triangulatePoints(lCam, rCam, mp1, mp2, result);

  std::cout << "4D Points: " << std::endl << result << std::endl;



}

