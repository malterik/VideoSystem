#pragma once 
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <vector>

class WindowManager
{
public:
    WindowManager();
    void addImage(cv::Mat image);
    void addImage(std::vector<cv::Mat> imageVector);

private:
    std::vector<cv::Mat> img_vector_;
};
