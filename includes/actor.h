//
// Created by sam on 2020-07-21.
//

#ifndef SDF_ACTOR_H
#define SDF_ACTOR_H


#include <iostream>
#include <Eigen/Dense>
#include "shader.h"
#include "poly_data.h"

class Actor {
public:
    Actor();
    Actor(GLsizei size);
    ~Actor();

    void setPolyData(PolyData *poly_data_ptr);
    void bind();
    void erase();

private:
    PolyData *poly_data_ptr_;
    GLuint *vao_;
    GLsizei vao_size_;
};


#endif //SDF_ACTOR_H
