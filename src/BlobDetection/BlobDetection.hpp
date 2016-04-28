#include <opencv2/opencv.hpp>
#include <vector>

class BlobDetection
{
public:
    BlobDetection();
    std::vector<cv::KeyPoint>getKeyPoints(cv::Mat image);
    cv::Mat getBlobImage(cv::Mat image);
private:
    cv::SimpleBlobDetector detector_;
    std::vector<cv::KeyPoint> keypoints_;
    cv::Mat blob_image_;
    cv::SimpleBlobDetector::Params blob_parameter_;
};
