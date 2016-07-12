#include "DisparityMap.hpp"

DisparityMap::DisparityMap() : 
  bp_iterations_(40),
  labels_(16),
  lambda_(20),
  smoothness_trunc_(2),
  pixel_(labels_)
{
}

unsigned int DisparityMap::DataCostStereo(const cv::Mat &left, const cv::Mat &right, int x, int y, int label)
{
    const int wradius = 2; // window radius, search block size is (wradius*2+1)*(wradius*2+1)

    int sum = 0;

    for(int dy=-wradius; dy <= wradius; dy++) {
        for(int dx=-wradius; dx <= wradius; dx++) {
            int a = left.at<uchar>(y+dy, x+dx);
            int b = right.at<uchar>(y+dy, x+dx-label);
            sum += abs(a-b);
        }
    }

    int avg = sum/((wradius*2+1)*(wradius*2+1)); // average difference

    return avg;
    //return std::min(avg, DATA_TRUNC);
}

unsigned int DisparityMap::SmoothnessCost(int i, int j)
{
    int d = i - j;

    return lambda_*std::min(abs(d), smoothness_trunc_);
}

void DisparityMap::InitDataCost(const std::string &left_file, const std::string &right_file, MRF2D &mrf)
{
    // Cache the data cost results so we don't have to recompute it every time

    // Force greyscale
    cv::Mat left = cv::imread(left_file.c_str(), 0);
    cv::Mat right = cv::imread(right_file.c_str(), 0);

    if(!left.data) {
      std::cout << "Error reading left image" << std::endl;
        exit(1);
    }

    if(!right.data) {
      std::cout << "Error reading right image" << std::endl;
        exit(1);
    }

    assert(left.channels() == 1);

    mrf.width = left.cols;
    mrf.height = left.rows;

    int total = mrf.width*mrf.height;

    mrf.grid.resize(total);

    // Initialise all messages to zero
    for(int i=0; i < total; i++) {
        for(int j=0; j < 5; j++) {
            for(int k=0; k < labels_; k++) {
                mrf.grid[i].msg[j][k] = 0;
            }
        }
    }

    // Add a border around the image
    int border = labels_;

    for(int y=border; y < mrf.height-border; y++) {
        for(int x=border; x < mrf.width-border; x++) {
            for(int i=0; i < labels_; i++) {
                mrf.grid[y*left.cols+x].msg[DATA][i] = DataCostStereo(left, right, x, y, i);
            }
        }
    }
}

void DisparityMap::SendMsg(MRF2D &mrf, int x, int y, DIRECTION direction)
{
    unsigned int new_msg[labels_];

    int width = mrf.width;

    for(int i=0; i < labels_; i++) {
        unsigned int min_val = UINT_MAX;

        for(int j=0; j < labels_; j++) {
            unsigned int p = 0;

            p += SmoothnessCost(i,j);
            p += mrf.grid[y*width+x].msg[DATA][j];

            // Exclude the incoming message direction that we are sending to
            if(direction != LEFT) p += mrf.grid[y*width+x].msg[LEFT][j];
            if(direction != RIGHT) p += mrf.grid[y*width+x].msg[RIGHT][j];
            if(direction != UP) p += mrf.grid[y*width+x].msg[UP][j];
            if(direction != DOWN) p += mrf.grid[y*width+x].msg[DOWN][j];

            min_val = std::min(min_val, p);
        }

        new_msg[i] = min_val;
    }

    for(int i=0; i < labels_; i++) {
        switch(direction) {
            case LEFT:
            mrf.grid[y*width + x-1].msg[RIGHT][i] = new_msg[i];
            break;

            case RIGHT:
            mrf.grid[y*width + x+1].msg[LEFT][i] = new_msg[i];
            break;

            case UP:
            mrf.grid[(y-1)*width + x].msg[DOWN][i] = new_msg[i];
            break;

            case DOWN:
            mrf.grid[(y+1)*width + x].msg[UP][i] = new_msg[i];
            break;

            default:
            assert(0);
            break;
        }
    }
}

void DisparityMap::BP(MRF2D &mrf, DIRECTION direction)
{
    int width = mrf.width;
    int height = mrf.height;

    switch(direction) {
        case RIGHT:
        for(int y=0; y < height; y++) {
            for(int x=0; x < width-1; x++) {
                SendMsg(mrf, x, y, direction);
            }
        }
        break;

        case LEFT:
        for(int y=0; y < height; y++) {
            for(int x=width-1; x >= 1; x--) {
                SendMsg(mrf, x, y, direction);
            }
        }
        break;

        case DOWN:
        for(int x=0; x < width; x++) {
            for(int y=0; y < height-1; y++) {
                SendMsg(mrf, x, y, direction);
            }
        }
        break;

        case UP:
        for(int x=0; x < width; x++) {
            for(int y=height-1; y >= 1; y--) {
                SendMsg(mrf, x, y, direction);
            }
        }
        break;

        case DATA:
        assert(0);
        break;
    }
}

unsigned int DisparityMap::MAP(MRF2D &mrf)
{
    // Finds the MAP assignment as well as calculating the energy

    // MAP assignment
    for(size_t i=0; i < mrf.grid.size(); i++) {
        unsigned int best = std::numeric_limits<unsigned int>::max();
        for(int j=0; j < labels_; j++) {
            unsigned int cost = 0;

            cost += mrf.grid[i].msg[LEFT][j];
            cost += mrf.grid[i].msg[RIGHT][j];
            cost += mrf.grid[i].msg[UP][j];
            cost += mrf.grid[i].msg[DOWN][j];
            cost += mrf.grid[i].msg[DATA][j];

            if(cost < best) {
                best = cost;
                mrf.grid[i].best_assignment = j;
            }
        }
    }

    int width = mrf.width;
    int height = mrf.height;

    // Energy
    unsigned int energy = 0;

    for(int y=0; y < mrf.height; y++) {
        for(int x=0; x < mrf.width; x++) {
            int cur_label = mrf.grid[y*width+x].best_assignment;

            // Data cost
            energy += mrf.grid[y*width+x].msg[DATA][cur_label];

            if(x-1 >= 0)     energy += SmoothnessCost(cur_label, mrf.grid[y*width+x-1].best_assignment);
            if(x+1 < width)  energy += SmoothnessCost(cur_label, mrf.grid[y*width+x+1].best_assignment);
            if(y-1 >= 0)     energy += SmoothnessCost(cur_label, mrf.grid[(y-1)*width+x].best_assignment);
            if(y+1 < height) energy += SmoothnessCost(cur_label, mrf.grid[(y+1)*width+x].best_assignment);
        }
    }

    return energy;
}
