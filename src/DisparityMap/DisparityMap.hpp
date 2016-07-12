#include <iostream>
#include <vector>
#include <string>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "Pixel.hpp"

enum DIRECTION {LEFT, RIGHT, UP, DOWN, DATA};




struct MRF2D
{
    std::vector <Pixel> grid;
    int width, height;
};

class DisparityMap
{
public:
  DisparityMap();

private:
  // Application specific code
  void InitDataCost(const std::string &left_file, const std::string &right_file, MRF2D &mrf);
  unsigned int DataCostStereo(const cv::Mat &left, const cv::Mat &right, int x, int y, int label);
  unsigned int SmoothnessCost(int i, int j);

  // Loppy belief propagation specific
  void BP(MRF2D &mrf, DIRECTION direction);
  void SendMsg(MRF2D &mrf, int x, int y, DIRECTION direction);
  unsigned int MAP(MRF2D &mrf);




  // parameters, specific to dataset
  int bp_iterations_ = 40;
  int labels_ = 16;
  int lambda_ = 20;
  int smoothness_trunc_ = 2;
  Pixel pixel_;
};
