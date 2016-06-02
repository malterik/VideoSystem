#include "ImageViewer.hpp"
#include "../WindowManager/WindowManager.hpp"
#include <array>

ImageViewer::ImageViewer(std::string windowName) :
  window_name_(windowName),
  camera_(LOCAL_CAM),
  camera_interface_(camera_)
{
  camera_interface_.setResolution(1280,720);
  cv::namedWindow(window_name_,1);
  cv::setMouseCallback(window_name_, ImageViewer::mouseCallback, this);
}

void ImageViewer::mouseCallback(int event, int x, int y)
{
  std::array<cv::Vec2i,5> windowInfo = WindowManager::getInstance().getInfo();
  if  ( event == cv::EVENT_LBUTTONDOWN )
  {
    std::cout << "Left button of the mouse is clicked - position (" << x << ", " << y << ")" << std::endl;
  }
  else if  ( event == cv::EVENT_RBUTTONDOWN )
  {
    std::cout << "Right button of the mouse is clicked - position (" << x << ", " << y << ")" << std::endl;
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
  while(1) {
    WindowManager::getInstance().reset();
    WindowManager::getInstance().addImage(img1);
    WindowManager::getInstance().addImage(img2);
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
