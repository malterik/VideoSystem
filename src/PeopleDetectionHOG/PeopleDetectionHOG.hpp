#include <opencv2/opencv.hpp>
#include <string>
#include <vector>
class PeopleDetectionHOG
{
public:
        PeopleDetectionHOG();
	void detectAndDisplay(cv::Mat image);

private:
	cv::HOGDescriptor hog_;
	std::string window_name_;
	std::vector<cv::Rect> found_;
	std::vector<cv::Rect> found_filtered_;
};
