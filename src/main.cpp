#include "Utils/DisableWarnings.hpp"
#include "Utils/Utils.hpp"
#include "CameraMatrix/CameraMatrix.hpp"

int main(void)
{
  CameraType type = DLINK_CAM_1;
  CameraMatrix cm(type,"config/CameraPose2.json");
  std::cout << "ExtrinsicMatrix" << std::endl << cm.getExtrinsicMatrix() << std::endl << std::endl;
  std::cout << "IntrinsicMatrix" << std::endl << cm.getIntrinsicMatrix() << std::endl << std::endl;
  std::cout << "CameraMatrix" << std::endl << cm.getCameraMatrix() << std::endl << std::endl;
  TransformationMatrix t = cm.getCamera2Ground();
  std::cout << "RotationMatrix" << std::endl << t.rotM() << std::endl << std::endl;
  std::cout << "PositionVector" << std::endl << t.posV() << std::endl << std::endl;

  return 1;
}
