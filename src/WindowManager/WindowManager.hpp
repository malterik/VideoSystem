#pragma once 
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <vector>

class WindowManager
{
public:
    static WindowManager& getInstance();
    void addImage(cv::Mat image);
    void addImage(std::vector<cv::Mat> imageVector);
    void reset();
    cv::Mat& showMultipleImages(int rows );
private:
    WindowManager();
    WindowManager(const WindowManager& wm);
    std::vector<cv::Mat> img_vector_;
    cv::Mat dst_;
    unsigned int dst_heigth_;
    unsigned int dst_width_;
    unsigned int dst_rows_;
    unsigned int dst_cols_;
};
