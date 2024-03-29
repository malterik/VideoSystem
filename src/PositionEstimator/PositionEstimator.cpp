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

std::vector<Eigen::Vector3d> PositionEstimator::triangulate(const std::vector<Eigen::Vector2d>& matchedPoints1, const std::vector<Eigen::Vector2d>& matchedPoints2) {
  std::vector<std::vector<cv::Point>> temp;
  std::vector<cv::Point> mp1, mp2;

  for (unsigned int i = 0; i < matchedPoints1.size(); i++) {
    mp1.emplace_back(matchedPoints1[i][0], matchedPoints1[i][1]);
    mp2.emplace_back(matchedPoints2[i][0], matchedPoints2[i][1]);
  }
  temp.push_back(mp1);
  temp.push_back(mp2);

  return triangulate(temp);
}

std::vector<Eigen::Vector3d> PositionEstimator::triangulate(const std::array<std::vector<Eigen::Vector2d>,2>& matchedPoints) {
  std::vector<std::vector<cv::Point>> temp;
  std::vector<cv::Point> mp1, mp2;

  for (unsigned int i = 0; i < matchedPoints[0].size(); i++) {
    mp1.emplace_back(matchedPoints[0][i][0], matchedPoints[0][i][1]);
    mp2.emplace_back(matchedPoints[1][i][0], matchedPoints[1][i][1]);
  }
  temp.push_back(mp1);
  temp.push_back(mp2);

  return triangulate(temp);
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

  cv::Mat mp1(N,1,CV_64FC2);
  cv::Mat mp2(N,1,CV_64FC2);
  cv::Mat mp1undistorted(N,1,CV_64FC2);
  cv::Mat mp2undistorted(N,1,CV_64FC2);
  cv::Mat Points4D;;
  cv::Mat lCam(3,4,CV_64FC1);
  cv::Mat rCam(3,4,CV_64FC1);
  cv::Mat intrinsicL(3,3,CV_64FC1);
  cv::Mat intrinsicR(3,3,CV_64FC1);
  cv::Mat rotationL(3,3,CV_64FC1);
  cv::Mat rotationR(3,3,CV_64FC1);
  cv::Mat translationL(3,1,CV_64FC1);
  cv::Mat translationR(3,1,CV_64FC1);
  cv::Mat distL(4, 1, cv::DataType<float>::type);
  cv::Mat distR(4, 1, cv::DataType<float>::type);
  cv::Mat R1, R2, P1, P2, Q;
  cv::Size newSize;
  cv::Mat undistortedImage;

  for (int i = 0; i < 2; i++) {
    distL.at<float>(i, 0) =  left_camera_matrix_.getDistortionCoefficients()[i];
    distR.at<float>(i, 0) =  right_camera_matrix_.getDistortionCoefficients()[i];
  }
  for(int x = 0; x < 3; x++) {
    translationL.at<double>(x) = left_camera_matrix_.getCamera2Ground().posV()(x);
    translationR.at<double>(x) = right_camera_matrix_.getCamera2Ground().posV()(x);
    for(int y = 0; y < 3; y++) {
      intrinsicL.at<double>(x,y) = left_camera_matrix_.getIntrinsicMatrix()(x,y);
      intrinsicR.at<double>(x,y) = right_camera_matrix_.getIntrinsicMatrix()(x,y);
      rotationL.at<double>(x,y) = left_camera_matrix_.getCamera2Ground().rotM()(x,y);
      rotationR.at<double>(x,y) = right_camera_matrix_.getCamera2Ground().rotM()(x,y);
    }
  }
  for(int x = 0; x < 3; x++) {
    for(int y = 0; y < 4; y++) {
      lCam.at<double>(x,y) = left_camera_matrix_.getCameraMatrix()(x,y);
      rCam.at<double>(x,y) = right_camera_matrix_.getCameraMatrix()(x,y);
    }
  }

  for (int i = 0; i < N; i++) {
    mp1.at<cv::Vec2d>(i,0)[0] = matchedPoints[0][i].x;
    mp1.at<cv::Vec2d>(i,0)[1] = matchedPoints[0][i].y;

    mp2.at<cv::Vec2d>(i,0)[0] = matchedPoints[1][i].x;
    mp2.at<cv::Vec2d>(i,0)[1] = matchedPoints[1][i].y;
  }
  if(!(mp1.empty() && mp2.empty())) {
    cv::stereoRectify(intrinsicL, distL, intrinsicR, distR, cv::Size(640,480), rotationR, translationR, R1, R2, P1, P2, Q,cv::CALIB_ZERO_DISPARITY, -1, newSize);
    cv::undistortPoints(mp1, mp1undistorted, intrinsicL, distL, R1, P1);
    cv::undistortPoints(mp2, mp2undistorted, intrinsicR, distR, R2, P2);
    cv::triangulatePoints(lCam, rCam, mp1undistorted, mp2undistorted, Points4D);
    // cv::triangulatePoints(lCam, rCam, mp1, mp2, Points4D);


  // std::cout << Points4D << std::endl;
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

CameraMatrix PositionEstimator::getCameraMatrix(Side cameraSide) {
  if(cameraSide == LEFT) {
    return left_camera_matrix_;
  } else {
    return right_camera_matrix_;
  }
}
