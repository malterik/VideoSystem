#include "PositionEstimator.hpp"
#include <opencv2/opencv.hpp>
#include "../Utils/print.hpp"

PositionEstimator::PositionEstimator(const CameraMatrix& leftCameraMatrix, const CameraMatrix& rightCameraMatrix) :
  left_camera_matrix_(leftCameraMatrix),
  right_camera_matrix_(rightCameraMatrix)
{
}
PositionEstimator::PositionEstimator(CameraType camera1, std::string path1, CameraType camera2, std::string path2) :
  left_camera_matrix_(camera1, path1),
  right_camera_matrix_(camera2, path2)
{
}

std::vector<Eigen::Vector3d> PositionEstimator::triangulate(const std::array<std::vector<Eigen::Vector2d>,2>& matchedPoints) {
  return triangulate(matchedPoints[0], matchedPoints[1]);
}

std::vector<Eigen::Vector3d> PositionEstimator::triangulate(const std::vector<std::vector<cv::Point>>& matchedPoints) {
  std::vector<Eigen::Vector3d> Points3D;
  if(matchedPoints[0].size() != matchedPoints[1].size()) {
     print(LogLevel::ERROR, "Number of points does not match!");
     return std::vector<Eigen::Vector3d>();
  }

  if(matchedPoints[0].empty() || matchedPoints[1].empty()) {
    print(LogLevel::ERROR, "No points for triangulation");
  }

  int N = matchedPoints[0].size();

  cv::Mat mp1(1,N,CV_64FC2);
  cv::Mat mp2(1,N,CV_64FC2);
  cv::Mat Points4D;;
  cv::Mat lCam(3,4,CV_64FC1);
  cv::Mat rCam(3,4,CV_64FC1);

  for(int x = 0; x < 3; x++) {
    for(int y = 0; y < 4; y++) {
      lCam.at<double>(x,y) = left_camera_matrix_.getCameraMatrix()(x,y);
      rCam.at<double>(x,y) = right_camera_matrix_.getCameraMatrix()(x,y);
    }
  }

  for (int i = 0; i < N; i++) {
    mp1.at<cv::Vec2d>(0,i)[0] = matchedPoints[0][i].x;
    mp1.at<cv::Vec2d>(0,i)[1] = matchedPoints[0][i].y;

    mp2.at<cv::Vec2d>(0,i)[0] = matchedPoints[1][i].x;
    mp2.at<cv::Vec2d>(0,i)[1] = matchedPoints[1][i].y;
  }
  if(!(mp1.empty() && mp2.empty())) {
    cv::triangulatePoints(lCam, rCam, mp1, mp2, Points4D);


  std::cout << Points4D << std::endl;
  //convert resulting points to a vector of Eigen Vectors
  for (int i = 0; i < Points4D.cols ; i++) {
    Eigen::Vector3d vec;
    vec(0) = Points4D.at<double>(0,i) / Points4D.at<double>(3,i);
    vec(1) = Points4D.at<double>(1,i) / Points4D.at<double>(3,i);
    vec(2) = Points4D.at<double>(2,i) / Points4D.at<double>(3,i);
    Points3D.push_back(vec);
  }
  std::cout << "3D Points" << std::endl;
  for(auto& it : Points3D)
    std::cout << it << std::endl;
  }
  return Points3D;
}
std::vector<Eigen::Vector3d> PositionEstimator::triangulate(const std::vector<Eigen::Vector2d>& matchedPoints1, const std::vector<Eigen::Vector2d>& matchedPoints2) {

  std::vector<Eigen::Vector3d> Points3D;
  if(matchedPoints1.size() != matchedPoints2.size()) {
     print(LogLevel::ERROR, "Number of points does not match!");
     return std::vector<Eigen::Vector3d>();
  }

  int N = matchedPoints1.size();

  cv::Mat mp1(1,N,CV_64FC2);
  cv::Mat mp2(1,N,CV_64FC2);
  cv::Mat Points4D;;
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

  cv::triangulatePoints(lCam, rCam, mp1, mp2, Points4D);


  std::cout << Points4D << std::endl;
  //convert resulting points to a vector of Eigen Vectors
  for (int i = 0; i < Points4D.cols ; i++) {
    Eigen::Vector3d vec;
    vec(0) = Points4D.at<double>(0,i) / Points4D.at<double>(3,i);
    vec(1) = Points4D.at<double>(1,i) / Points4D.at<double>(3,i);
    vec(2) = Points4D.at<double>(2,i) / Points4D.at<double>(3,i);
    Points3D.push_back(vec);
  }
  std::cout << "3D Points" << std::endl;
  for(auto& it : Points3D)
    std::cout << it << std::endl;
  return Points3D;
}

CameraMatrix PositionEstimator::getCameraMatrix(Side cameraSide) {
  if(cameraSide == LEFT) {
    return left_camera_matrix_;
  } else {
    return right_camera_matrix_;
  }
}
