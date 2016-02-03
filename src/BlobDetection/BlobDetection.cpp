#include "BlobDetection.hpp"

BlobDetection::BlobDetection() {
    // blob_parameter_.minThreshold = 10;
    // blob_parameter_.maxThreshold = 200;    
    // blob_parameter_.filterByColor = true;
    // blob_parameter_.blobColor = 50;
    blob_parameter_.filterByArea = true;
    blob_parameter_.minArea = 1500;
    detector_ = cv::SimpleBlobDetector(blob_parameter_);
    
}

    std::vector<cv::KeyPoint> BlobDetection::getKeyPoints(cv::Mat image){
    detector_.detect(image, keypoints_);
    return keypoints_;
}

cv::Mat BlobDetection::getBlobImage(cv::Mat image) {
    detector_.detect(image, keypoints_);
    cv::drawKeypoints(image, keypoints_,blob_image_, cv::Scalar(0,0,255), cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS); 
    return blob_image_;
}
