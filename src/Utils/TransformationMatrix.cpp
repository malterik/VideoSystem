#include "TransformationMatrix.hpp"
#include <fstream>

TransformationMatrix::TransformationMatrix(const Eigen::Matrix3d& rotation_matrix, const Eigen::Vector3d& position_vector) : 
    rotation_matrix_(rotation_matrix), position_vector_(position_vector)
{

    // invert the vector and matrix for future use
    rotation_matrix_inv_ = rotation_matrix_.inverse();
    position_vector_inv_ = ( rotation_matrix_inv_ * -1 ) * position_vector_;
    
    // Construct the actual transformation matrix
    transformation_matrix_ = Eigen::Matrix4d::Zero();
    transformation_matrix_.block<3,3>(0,0) = rotation_matrix_; 
    transformation_matrix_.block<3,1>(0,3) = position_vector_;
    transformation_matrix_(3,3) = 1;
}

TransformationMatrix::TransformationMatrix(const std::string& filename) : 
    filename_(filename)
{
    json matrixConfig; 
    std::ifstream configFile (filename_);
    if (configFile.is_open()) {
        std::string str((std::istreambuf_iterator<char>(configFile)),
                         std::istreambuf_iterator<char>());
        matrixConfig = json::parse(str);    
        // rotM = matrixConfig["rotM"];
        configFile.close();
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                rotation_matrix_(i,j) = matrixConfig["rotM"][i*3+j]; 
            }
        }
        for (int i = 0; i < 3; i++) {
            position_vector_(i) = matrixConfig["posV"][i];
        }

        // invert the vector and matrix for future use
        rotation_matrix_inv_ = rotation_matrix_.inverse();
        position_vector_inv_ = ( rotation_matrix_inv_ * -1 ) * position_vector_;

        // Construct the actual transformation matrix
        transformation_matrix_ = Eigen::Matrix4d::Zero();
        transformation_matrix_.block<3,3>(0,0) = rotation_matrix_; 
        transformation_matrix_.block<3,1>(0,3) = position_vector_;
        transformation_matrix_(3,3) = 1;

        std::cout << transformation_matrix_ << std::endl;

    } else std::cout << "Unable to open people detection config file" << std::endl; 
}

const TransformationMatrix TransformationMatrix::inverse() const {

    return TransformationMatrix(rotation_matrix_inv_, position_vector_inv_);
}


const Eigen::Vector3d TransformationMatrix::transform(const Eigen::Vector3d& vec) const {
    
    // Make homogenous coordinates
    Eigen::Vector4d vecHomo(vec(0), vec(1), vec(2), 1);
    Eigen::Vector4d vecResult(0,0,0,1);

    vecResult = transformation_matrix_ * vecHomo;

    return Eigen::Vector3d(vecResult.block<3,1>(0,0));
}


const Eigen::Matrix4d& TransformationMatrix::getMatrix() const {
    return transformation_matrix_;

}
const Eigen::Matrix3d& TransformationMatrix::rotM() const {
    return rotation_matrix_;

}
const Eigen::Vector3d& TransformationMatrix::posV() const {
    return position_vector_;
}
