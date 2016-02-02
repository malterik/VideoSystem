#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <string>

class FaceDetection
{
public:
	FaceDetection(std::string faceConfig, std::string eyeConfig);
	void detectAndDisplay(cv::Mat image);

private:
	std::string face_cascade_name_; // = "haarcascade_frontalface_alt.xml";
	std::string eyes_cascade_name_; // = "haarcascade_eye_tree_eyeglasses.xml";
	std::string window_name_;  
	cv::CascadeClassifier face_cascade_;
	cv::CascadeClassifier eyes_cascade_;
};
