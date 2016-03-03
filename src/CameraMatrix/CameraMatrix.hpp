#pragma once
#include <string>

class CameraMatrix
{
public:
    CameraMatrix();

private:

    void readConfig(); 

    double c_x_;
    double c_y_;
    double f_x_;
    double f_y_;

    std::string FILE_NAME_;

};
