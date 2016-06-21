#pragma once

enum CameraType {
  IP_CAM1,
  IP_CAM2,
  LOCAL_CAM,
  DLINK_CAM

};

struct Camera {
  CameraType ct;
  int img_width;
  int img_height;
};
