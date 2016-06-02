#include "ImageWriter.hpp"
#include "../Utils/print.hpp"

ImageWriter::ImageWriter(const std::string& imageFolder) :
  counter_(0),
  image_folder_(imageFolder)
{
}

void ImageWriter::writeImage(const cv::Mat& img, std::string filename) {
  std::string path = image_folder_;
  path += filename;
  path += std::to_string(counter_);
  path += ".png";
  cv::imwrite(path, img);
  print(LogLevel::INFO, "Image written to %s", path.c_str());
  counter_++;
}

void ImageWriter::resetCounter() {
  counter_ = 0;
}



