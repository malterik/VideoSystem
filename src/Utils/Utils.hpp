#pragma once

enum CameraType {
  IP_CAM1,
  IP_CAM2,
  LOCAL_CAM,
  DLINK_CAM_1,
  DLINK_CAM_2

};

struct Camera {
  CameraType ct;
  int img_width;
  int img_height;
};
