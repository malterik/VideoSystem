#pragma once

#include <opencv2/opencv.hpp>
#include <string>
#include <vector>
#include "../ImageSubtractor/ImageSubtractor.hpp"
class PeopleDetection
{
public:
        PeopleDetection();
        const std::vector<cv::Rect>& detect(const cv::Mat& image);
        void debugImage() const;
        void reset();
        void writeConfig();
        void readConfig();
        void showTrackbars(const char* windowName);

private:
        //Images
        cv::Mat background_image_;
        cv::Mat blur_img_;
        cv::Mat contour_img_;
        cv::Mat image_;
        cv::Mat kernel_;
        cv::Mat thresh_img_;

        //Vectors
        std::vector<std::vector<cv::Point>> contours_;
        std::vector<std::vector<cv::Point> > contours_poly;
        std::vector<cv::Vec4i> hierarchy_;
        std::vector<cv::Rect> people_candidates_;

        //Pointer for the backgroundsubtractor
        cv::Ptr<cv::BackgroundSubtractor> p_background_subtractor_;
        cv::Ptr<cv::BackgroundSubtractor> p_background_subtractor2_;
        cv::Ptr<cv::BackgroundSubtractor> p_background_subtractor3_;
        cv::Ptr<ImageSubtractor> p_image_subtractor_;

        //Parameter
        int DILATE_KERNEL_SIZE_;
        int BLUR_KERNEL_SIZE_;
        int THRESHOLD_;
        int MIN_BOUNDING_BOX_AREA_;
        std::string FILE_NAME_;


        //Setter and getter functions
public:
        void setDilateKernelSize(int dilateKernelSize);
        int getDilateKernelSize();

        void setBlurKernelSize(int blurKernelSize);
        int getBlurKernelSize();

        void setThreshold(int threshold);
        int getThreshold();

        void setMinBoundingBoxArea(int minBoundingBoxArea);
        int getMinBoundingBoxArea();
};
