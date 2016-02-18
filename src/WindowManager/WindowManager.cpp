#include "WindowManager.hpp"
#include <iostream>

WindowManager::WindowManager() {
}
WindowManager& WindowManager::getInstance() {
    static WindowManager instace_;
    return instace_;
}
void WindowManager::reset() {
    img_vector_.clear();
}

void WindowManager::addImage(cv::Mat image) {
    if(image.type() == CV_8UC1)
    {
        // std::cout << "\e[31m A binary image was added. It will be converted to 8UC3!\033[0m" << std::endl;
        cv::cvtColor(image,image,CV_GRAY2RGB);
    }
    img_vector_.push_back(image); 
}

void WindowManager::addImage(std::vector<cv::Mat> imageVector) {
   img_vector_.insert(img_vector_.end(), imageVector.begin(),imageVector.end()); 
}

cv::Mat& WindowManager::showMultipleImages(int rows) {
    if(img_vector_.empty()) {
        std::cout << "Image vector empty!" << std::endl;
        return dst_;
    }

    dst_rows_ = rows;
    dst_cols_ = ceil((float) img_vector_.size() / (float) dst_rows_ ); 

    dst_heigth_ = img_vector_[0].rows * dst_rows_; 
    dst_width_ = img_vector_[0].cols * dst_cols_; 

    dst_ = cv::Mat(dst_heigth_, dst_width_, CV_8UC3, cv::Scalar(0,0,0));    

    unsigned int imageCounter = 0;
    for (unsigned int i = 0; i < dst_rows_; i++) {
        for (unsigned int j = 0; j < dst_cols_; j++) {
             
            int index = i * dst_cols_ + j;
            int currentHeight = img_vector_[index].rows;
            int currentWidth = img_vector_[index].cols;
            cv::Rect roi(cv::Rect(j * currentWidth, i * currentHeight, currentWidth, currentHeight));
            cv::Mat targetROI = dst_(roi);
            img_vector_[index].copyTo(targetROI);
            if(imageCounter >= img_vector_.size()) {
                goto end;
            }
        

            imageCounter++;
        }

    }


    end : return dst_;
}

void WindowManager::drawBoundingBox(std::vector<cv::Rect> bBox, const cv::Mat& img) {
    cv::Mat bBoxImg;    
    img.copyTo(bBoxImg);
    for( unsigned int i = 0; i< bBox.size(); i++ )
    {
        cv::Scalar color = cv::Scalar( 255, 0, 0 );
        rectangle(bBoxImg, bBox[i].tl(),bBox[i].br(), color, 2, 8, 0 );
    }
    addImage(bBoxImg);
}
