//
// Created by sam on 2020-07-21.
//

#ifndef SDF_ACTOR_H
#define SDF_ACTOR_H


#include <iostream>
#include <Eigen/Dense>

typedef Eigen::Array<float, 1, 2> Arr2f;
typedef Eigen::Array<float, 1, 3> Arr3f;
typedef Eigen::Array<float, 1, 4> Arr4f;
typedef Eigen::Matrix<float, 6, 2, Eigen::RowMajor> Mat6_2f;
typedef Eigen::Matrix<float, 36, 2, Eigen::RowMajor> Mat36_2f;
typedef Eigen::Matrix<float, 36, 3, Eigen::RowMajor> Mat36_3f;
typedef Eigen::Matrix<float, 36, 4, Eigen::RowMajor> Mat36_4f;
typedef Eigen::Matrix<float, 36, 12, Eigen::RowMajor> Mat36_12f;

class Actor {
public:
    Actor();
    ~Actor();

    Mat36_12f genCube();
};


#endif //SDF_ACTOR_H
