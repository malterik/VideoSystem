#include "ImageViewer.hpp"
#include "../WindowManager/WindowManager.hpp"
#include <array>
#include "../Utils/print.hpp"

ImageViewer::ImageViewer(std::string windowName, Camera camLeft, Camera camRight) :
  window_name_(windowName),
  camera_left_(camLeft),
  camera_right_(camRight),
  camera_interface_left_(camera_left_.ct),
  camera_interface_right_(camera_right_.ct),
  image_writer_left_("Images/"),
  image_writer_right_("Images/"),
  visualizer_(),
  image_coordinates_l_(),
  image_coordinates_r_(),
  rng_(0xFFFFFFFF),
  color_counter_(2),
  circle_color_()
{
  camera_interface_left_.setResolution(camera_left_.img_height, camera_left_.img_height);
  camera_interface_right_.setResolution(camera_right_.img_height, camera_right_.img_height);
  print(LogLevel::DEBUG, "Camera Left %d", camera_left_.ct);
  print(LogLevel::DEBUG, "Camera Right %d", camera_right_.ct);
  cv::namedWindow(window_name_,1);
  cv::setMouseCallback(window_name_, ImageViewer::mouseCallback, this);
}

void ImageViewer::mouseCallback(int event, int x, int y)
{
  if  ( event == cv::EVENT_LBUTTONDOWN )
  {
    std::array<int,5> windowInfo = WindowManager::getInstance().getInfo();

    if(color_counter_== 2) {
      int icolor = (unsigned) rng_;
      circle_color_= cv::Scalar( icolor&255, (icolor>>8)&255, (icolor>>16)&255 );
      color_counter_ = 0;
    }

    if(x < (windowInfo[1] / windowInfo[3])) {
      WindowManager::getInstance().drawCircle(cv::Point(x,y), circle_color_, 0);
      color_counter_++;
      image_coordinates_l_.emplace_back(x,y);
      std::cout << cv::Point(x,y) << std::endl;
    } else {
      x -= (windowInfo[1] / windowInfo[3]);
      WindowManager::getInstance().drawCircle(cv::Point(x,y), circle_color_, 1);
      color_counter_++;
      image_coordinates_r_.emplace_back(x,y);
      std::cout << cv::Point(x,y) << std::endl;
    }
  }
  if  ( event == cv::EVENT_RBUTTONDOWN ) {
    // std::cout << "Left Coords: " << std::endl << image_coordinates_l_  << std::endl;
    // std::cout << "Right Coords: " << std::endl << image_coordinates_r_  << std::endl;
  }
}

void ImageViewer::mouseCallback(int event, int x, int y, int, void* this_) {
  static_cast<ImageViewer*>(this_)->mouseCallback(event, x, y);
}

void ImageViewer::showImage(const cv::Mat& img) {
  while(1) {
    WindowManager::getInstance().reset();
    WindowManager::getInstance().addImage(img);
    char key = (char)cv::waitKey(10);
    if( key  == 27 ) {
      break;
    }
    cv::imshow(window_name_, WindowManager::getInstance().showMultipleImages(1));
  }
}

void ImageViewer::dualView(const cv::Mat& img1, const cv::Mat& img2) {
  WindowManager::getInstance().reset();
  WindowManager::getInstance().addImage(img1);
  WindowManager::getInstance().addImage(img2);
  while(1) {
    char key = (char)cv::waitKey(10);
    if( key  == 27 ) {
      break;
    }
    cv::imshow(window_name_, WindowManager::getInstance().showMultipleImages(1));
  }
}

void ImageViewer::showCamera(CameraSide cs) {
  while(1) {
    WindowManager::getInstance().reset();
    if (cs == LEFT_CAM) {
      cv::Mat frameLeft = camera_interface_left_.getImage();
      WindowManager::getInstance().addImage(frameLeft);
    } else if(cs == RIGHT_CAM) {
      cv::Mat frameRight = camera_interface_right_.getImage();
      WindowManager::getInstance().addImage(frameRight);
    } else if(cs == BOTH) {
      cv::Mat frameLeft = camera_interface_left_.getImage();
      cv::Mat frameRight = camera_interface_right_.getImage();
      WindowManager::getInstance().addImage(frameLeft);
      WindowManager::getInstance().addImage(frameRight);
    }
    char key = (char)cv::waitKey(10);
    if( key  == 27 ) {
      break;
    }
    cv::imshow(window_name_, WindowManager::getInstance().showMultipleImages(1) );
  }
}

void ImageViewer::snapshots(CameraSide cs) {
  while(1) {
    WindowManager::getInstance().reset();
    cv::Mat frameLeft;
    cv::Mat frameRight;
    if (cs == LEFT_CAM) {
      frameLeft = camera_interface_left_.getImage();
      WindowManager::getInstance().addImage(frameLeft);
    } else if(cs == RIGHT_CAM) {
      frameRight = camera_interface_right_.getImage();
      WindowManager::getInstance().addImage(frameRight);
    } else if(cs == BOTH) {
      frameLeft = camera_interface_left_.getImage();
      frameRight = camera_interface_right_.getImage();
      WindowManager::getInstance().addImage(frameLeft);
      WindowManager::getInstance().addImage(frameRight);
    }
    char key = (char)cv::waitKey(10);
    if( key  == 27 ) {
      break;
    } else if(key == 32) {
      if (cs == LEFT_CAM) {
        image_writer_left_.writeImage(frameLeft,"cameraLeft");
      } else if(cs == RIGHT_CAM) {
        image_writer_right_.writeImage(frameRight,"cameraRight");
      } else if(cs == BOTH) {
        image_writer_left_.writeImage(frameLeft,"cameraLeft");
        image_writer_right_.writeImage(frameRight,"cameraRight");
      }
    }
    cv::imshow(window_name_, WindowManager::getInstance().showMultipleImages(1) );
  }
}
std::array<std::vector<Eigen::Vector2d>,2> ImageViewer::pointPairs(const cv::Mat& img1, const cv::Mat& img2, PositionEstimator& pe) {
  std::array<std::vector<Eigen::Vector2d>,2> result;
  image_coordinates_l_.clear();
  image_coordinates_r_.clear();
  std::vector<Eigen::Vector3d> points;
  WindowManager::getInstance().reset();
  WindowManager::getInstance().addImage(img1);
  WindowManager::getInstance().addImage(img2);
  while(1) {
    char key = (char)cv::waitKey(10);
    if( key  == 27 ) {
      break;
    } else if ( key == 10) {
      result[0] = image_coordinates_l_;
      result[1] = image_coordinates_r_;
      std::vector<Eigen::Vector3d> points =  pe.triangulate(result);
      cv::imshow("Map", visualizer_.showMap(points));
    }
    cv::imshow(window_name_, WindowManager::getInstance().showMultipleImages(1));

  }
  result[0] = image_coordinates_l_;
  result[1] = image_coordinates_r_;

  return result;
}
