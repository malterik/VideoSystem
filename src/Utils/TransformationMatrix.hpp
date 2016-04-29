#pragma once

#include "../Eigen/Dense"
#include "../json/json.hpp"
#include <string>

using json = nlohmann::json;

class TransformationMatrix
{
public:
  TransformationMatrix(const Eigen::Matrix3d& rotation_matrix, const Eigen::Vector3d& position_vector);
  TransformationMatrix(const std::string& filename);

  const Eigen::Vector3d transform(const Eigen::Vector3d& vec) const;

  const Eigen::Matrix4d& getMatrix() const;
  const Eigen::Matrix3d& rotM() const;
  const Eigen::Vector3d& posV() const;

  const TransformationMatrix inverse() const;

private:
  Eigen::Matrix3d rotation_matrix_;
  Eigen::Vector3d position_vector_;

  Eigen::Matrix3d rotation_matrix_inv_;
  Eigen::Vector3d position_vector_inv_;

  Eigen::Matrix4d transformation_matrix_;

  std::string filename_;
};
