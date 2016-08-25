#include "Visualizer.hpp"
#include "../WindowManager/WindowManager.hpp"

Visualizer::Visualizer() :
  map_(530,510, CV_8UC3, cv::Scalar(255,255,255))
{
  clearMap();
}

cv::Mat& Visualizer::showMap(std::vector<Eigen::Vector3d> points) {
  clearMap();
  if(!points.empty()) {
    for(auto it : points) {
      cv::circle(map_,cv::Point(250 - it[0] , 500 - it[2] ), 3, cv::Scalar(255,0,0), 2);
    }
  }
  return map_;
  // WindowManager::getInstance().addImage(map_);
}

void Visualizer::clearMap() {
  map_.setTo(cv::Scalar(255,255,255));
  //x axis
  cv::line(map_, cv::Point(250,520), cv::Point(250,0), cv::Scalar(0,0,0));
  //y axis
  cv::line(map_, cv::Point(0,500), cv::Point(500,500), cv::Scalar(0,0,0));

  //ticks
  for (int i = 0; i < 501; i+=10) {
    if(i % 100 == 0) {
      cv::line(map_, cv::Point(i,502), cv::Point(i,498), cv::Scalar(0,0,0));
      cv::line(map_, cv::Point(246,i), cv::Point(254,i), cv::Scalar(0,0,255), 2);
    } else{
      cv::line(map_, cv::Point(i,502), cv::Point(i,498), cv::Scalar(0,0,0));
      cv::line(map_, cv::Point(248,i), cv::Point(252,i), cv::Scalar(0,0,0));
    }
  }

  //text
  cv::putText(map_, "0", cv::Point(252,510), cv::FONT_HERSHEY_COMPLEX_SMALL, 0.5, cv::Scalar(0,0,255));
  cv::putText(map_, "1", cv::Point(255,404), cv::FONT_HERSHEY_COMPLEX_SMALL, 0.5, cv::Scalar(0,0,255));
  cv::putText(map_, "2", cv::Point(255,304), cv::FONT_HERSHEY_COMPLEX_SMALL, 0.5, cv::Scalar(0,0,255));
  cv::putText(map_, "3", cv::Point(255,204), cv::FONT_HERSHEY_COMPLEX_SMALL, 0.5, cv::Scalar(0,0,255));
  cv::putText(map_, "4", cv::Point(255,104), cv::FONT_HERSHEY_COMPLEX_SMALL, 0.5, cv::Scalar(0,0,255));
  cv::putText(map_, "5", cv::Point(255,8), cv::FONT_HERSHEY_COMPLEX_SMALL, 0.5, cv::Scalar(0,0,255));

  cv::line(map_, cv::Point(150,504), cv::Point(150,496), cv::Scalar(0,0,255), 2);
  cv::putText(map_, "-1", cv::Point(140,515), cv::FONT_HERSHEY_COMPLEX_SMALL, 0.5, cv::Scalar(0,0,255));
  cv::line(map_, cv::Point(50,504), cv::Point(50,496), cv::Scalar(0,0,255), 2);
  cv::putText(map_, "-2", cv::Point(40,515), cv::FONT_HERSHEY_COMPLEX_SMALL, 0.5, cv::Scalar(0,0,255));

  cv::line(map_, cv::Point(350,504), cv::Point(350,496), cv::Scalar(0,0,255), 2);
  cv::putText(map_, "1", cv::Point(346,515), cv::FONT_HERSHEY_COMPLEX_SMALL, 0.5, cv::Scalar(0,0,255));
  cv::line(map_, cv::Point(450,504), cv::Point(450,496), cv::Scalar(0,0,255), 2);
  cv::putText(map_, "2", cv::Point(446,515), cv::FONT_HERSHEY_COMPLEX_SMALL, 0.5, cv::Scalar(0,0,255));
  cv::line(map_, cv::Point(250,504), cv::Point(250,496), cv::Scalar(0,0,255), 2);

}
