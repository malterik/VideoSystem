#include "ImageSubtractor.hpp"
#include "../Utils/print.hpp"


ImageSubtractor::ImageSubtractor(const cv::Mat& initialBackground) : background_image_(initialBackground.clone())
{
}


void ImageSubtractor::setBackground( const cv::Mat& img) {
  background_image_ = img.clone();
}

cv::Mat& ImageSubtractor::subtractBackground(const cv::Mat& img) {
  cv::subtract(background_image_,img,diff_image_);
  return diff_image_;
}

cv::Mat& ImageSubtractor::getBackground() {
  return background_image_;
}

cv::Mat& ImageSubtractor::getDiffImage() {
  return diff_image_;
}
