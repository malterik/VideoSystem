#include "StereoMatcher.hpp"
#include <stdlib.h>

StereoMatcher::StereoMatcher():
  point_pairs_(),
  THRESHOLD_(30)
{
}

std::vector<std::vector<cv::Point>> StereoMatcher::findPointPairs(std::vector<cv::Rect> peopleL, std::vector<cv::Rect> peopleR) {
  std::vector<std::vector<cv::Rect>> matchedPairs;
  std::vector<std::vector<cv::Point>> result;
  std::vector<cv::Rect> match;
  for(auto it : peopleL) {
    for(unsigned int i = 0; i < peopleR.size(); i++) {
      if(std::abs(it.height - peopleR[i].height) < THRESHOLD_ && std::abs(it.width- peopleR[i].width) < THRESHOLD_){
        //Matching Boundig boxes are found
        match.push_back(it);
        match.push_back(peopleR[i]);
        peopleR.erase(peopleR.begin()+i);
        matchedPairs.push_back(match);
      }
    }
  }

  for(auto pair : matchedPairs) {
    std::vector<cv::Point> temp;
    // top left corner
    temp.push_back( pair[0].tl());
    temp.push_back( pair[1].tl());
    result.push_back(temp);
    temp.clear();
    //top right corner
    temp.emplace_back(pair[0].br().x, pair[0].tl().y);
    temp.emplace_back(pair[1].br().x, pair[1].tl().y);
    result.push_back(temp);
    temp.clear();
    //bottom left corner
    temp.emplace_back(pair[0].tl().x, pair[0].br().y);
    temp.emplace_back(pair[1].tl().x, pair[1].br().y);
    result.push_back(temp);
    temp.clear();
    //bottom right corner
    temp.push_back( pair[0].br());
    temp.push_back( pair[1].br());
    result.push_back(temp);
    temp.clear();
    //middle point
    int add_x1 =pair[0].br().x - pair[0].tl().x;
    int add_x2 =pair[1].br().x - pair[1].tl().x;
    int add_y1 =pair[0].br().y - pair[0].tl().y;
    int add_y2 =pair[1].br().y - pair[1].tl().y;
    temp.emplace_back(pair[0].tl().x + (add_x1/2), pair[0].tl().y + (add_y1/2));
    temp.emplace_back(pair[1].tl().x + (add_x2/2), pair[1].tl().y + (add_y2/2));
    result.push_back(temp);
    temp.clear();
  }
  return result;
}
