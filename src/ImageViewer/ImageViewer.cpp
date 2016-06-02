#include "ImageViewer.hpp"
#include "../WindowManager/WindowManager.hpp"
#include <array>
#include "../Utils/print.hpp"

ImageViewer::ImageViewer(std::string windowName) :
  window_name_(windowName),
  camera_(LOCAL_CAM),
  camera_interface_(camera_),
  image_coordinates_l_(),
  image_coordinates_r_(),
  rng_(0xFFFFFFFF),
  color_counter_(2),
  circle_color_()
{
  camera_interface_.setResolution(1280,720);
  cv::namedWindow(window_name_,1);
  cv::setMouseCallback(window_name_, ImageViewer::mouseCallback, this);
}

void ImageViewer::mouseCallback(int event, int x, int y)
{
  //Random Generator for random colors
  if  ( event == cv::EVENT_LBUTTONDOWN )
  {
    std::array<int,5> windowInfo = WindowManager::getInstance().getInfo();

    if(color_counter_== 2) {
      int icolor = (unsigned) rng_;
      circle_color_= cv::Scalar( icolor&255, (icolor>>8)&255, (icolor>>16)&255 );
      color_counter_ = 0;
      std::cout << "nEW COLOR!!" << std::endl;
    }

    if(x < (windowInfo[1] / windowInfo[3])) {
      WindowManager::getInstance().drawCircle(cv::Point(x,y), circle_color_, 0);
      color_counter_++;
      image_coordinates_l_.emplace_back(x,y);
      std::cout << circle_color_<< std::endl;
    } else {
      x -= (windowInfo[1] / windowInfo[3]);
      WindowManager::getInstance().drawCircle(cv::Point(x,y), circle_color_, 1);
      color_counter_++;
      image_coordinates_r_.emplace_back(x,y);
      std::cout << circle_color_<< std::endl;
    }
  }
  if  ( event == cv::EVENT_RBUTTONDOWN ) {
    std::cout << "Left Coords: " << std::endl << image_coordinates_l_  << std::endl;
    std::cout << "Right Coords: " << std::endl << image_coordinates_r_  << std::endl;
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

void ImageViewer::showCamera(Camera camera) {
  camera_ = camera;
  camera_interface_.reset(camera);
  while(1) {
    WindowManager::getInstance().reset();
    cv::Mat frame = camera_interface_.getImage();
    WindowManager::getInstance().addImage(frame);
    char key = (char)cv::waitKey(10);
    if( key  == 27 ) {
      break;
    }
    cv::imshow(window_name_, WindowManager::getInstance().showMultipleImages(1) );
  }
}

