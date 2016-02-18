#include <opencv2/opencv.hpp>
#include <string>
#include <vector>
class PeopleDetection
{
public:
        PeopleDetection();
        std::vector<cv::Rect> detect(cv::Mat image);
        void debugImage();
        void reset();

private:
        cv::Mat image_;
        cv::Ptr<cv::BackgroundSubtractorMOG> p_background_subtractor_;
        int kernel_size_ =4;
        cv::Mat kernel_;
        std::vector<std::vector<cv::Point>> contours_;
        std::vector<cv::Vec4i> hierarchy_;
        cv::Mat background_image_;  
        cv::Mat contour_img_;
        cv::Mat thresh_img_;
        cv::Mat blur_img_;
        std::vector<std::vector<cv::Point> > contours_poly; 
        std::vector<cv::Rect> boundRect;
        std::vector<cv::Point2f>center;
        std::vector<float>radius;
        std::vector<cv::Rect> people_candidates_;
        std::vector<std::vector<cv::Point> > contours_poly_candidates_; 
};
