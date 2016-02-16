#include <opencv2/opencv.hpp>
#include <string>
#include <vector>
class PeopleDetection
{
public:
        PeopleDetection();
	void detect(cv::Mat image);
        void debugImage();

private:
        cv::Mat image_;
	std::vector<cv::Rect> found_;
	std::vector<cv::Rect> found_filtered_;
        cv::Ptr<cv::BackgroundSubtractorMOG> p_background_subtractor_;
        int kernel_size_ =4;
        cv::Mat kernel_;
        std::vector<std::vector<cv::Point>> contours_;
        std::vector<cv::Vec4i> hierarchy_;
        cv::Mat background_image_;  
        cv::Mat morph_img_;
        std::vector<std::vector<cv::Point> > contours_poly; 
        std::vector<cv::Rect> boundRect;
        std::vector<cv::Point2f>center;
        std::vector<float>radius;
};
