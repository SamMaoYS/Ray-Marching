//
// Created by sam on 2020-07-25.
//

#include "poly_data.h"

PolyData::PolyData() {
    vbo_ = new GLuint;
    vbo_size_ = 1;
    glGenBuffers(vbo_size_, vbo_);
}

PolyData::PolyData(GLsizei size) {
    vbo_ = new GLuint;
    vbo_size_ = size;
    glGenBuffers(vbo_size_, vbo_);
}

void PolyData::genCube() {
    Arr3f a0(0.5, 0.5, 0.5);
    Arr3f b0(0.5, 0.5, -0.5);
    Arr3f c0(-0.5, 0.5, -0.5);
    Arr3f d0(-0.5, 0.5, 0.5);

    Arr3f a1(0.5, -0.5, 0.5);
    Arr3f b1(0.5, -0.5, -0.5);
    Arr3f c1(-0.5, -0.5, -0.5);
    Arr3f d1(-0.5, -0.5, 0.5);

    Arr3f n0(0, 0, 1);
    Arr3f n1(0, 0, -1);
    Arr3f n2(1, 0, 0);
    Arr3f n3(-1, 0, 0);
    Arr3f n4(0, 1, 0);
    Arr3f n5(0, -1, 0);

    Arr2f t0(0, 0);
    Arr2f t1(0, 1);
    Arr2f t2(1, 0);
    Arr2f t3(1, 1);

    Arr4f white(1, 1, 1, 1);

    MatXf pos(36, 3);
    pos << d0, d1, a1, a1, a0, d0, // front face
            b0, b1, c1, c1, c0, b0, // back face
            a0, a1, b1, b1, b0, a0, // right face
            c0, c1, d1, d1, d0, c0, // left face
            c0, d0, a0, a0, b0, c0, // top face
            d1, c1, b1, b1, a1, d1; // bottom face

    MatXf normals(36, 3);
    normals << n0.replicate(6, 1),
            n1.replicate(6, 1),
            n2.replicate(6, 1),
            n3.replicate(6, 1),
            n4.replicate(6, 1),
            n5.replicate(6, 1);

    MatXf t_rec(6, 2);
    t_rec << t1, t0, t2, t2, t3, t1;
    MatXf t_coords = t_rec.replicate(6, 1);

    MatXf colors = white.replicate(36, 1);

    MatXf cube(36, 12);
    cube.block<36, 3>(0, 0) = pos;
    cube.block<36, 4>(0, 3) = colors;
    cube.block<36, 3>(0, 7) = normals;
    cube.block<36, 2>(0, 10) = t_coords;

    data_ = cube;

    fields_.resize(4);
    fields_[0] = VertexField(0, 3, GL_FLOAT, GL_FALSE, 0 *sizeof(float));
    fields_[1] = VertexField(1, 4, GL_FLOAT, GL_FALSE, 3 * sizeof(float));
    fields_[2] = VertexField(2, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float));
    fields_[3] = VertexField(3, 2, GL_FLOAT, GL_FALSE, 10 * sizeof(float));

    field_size_ = this->calFieldSize();
    data_size_ = sizeof(GLfloat)*data_.size();
    this->bindVBO();
}

void bind(PolyData *poly_data_ptr) {
    glBindBuffer(GL_ARRAY_BUFFER, *poly_data_ptr->vbo_);
}

void PolyData::bindVBO() {
    glBindBuffer(GL_ARRAY_BUFFER, *vbo_);
    glBufferData(GL_ARRAY_BUFFER, data_size_, this->data(), GL_STATIC_DRAW);
}

GLuint PolyData::calFieldSize() const {
    GLuint size = 0;
    for (int i = 0; i < fields_.size(); ++i)
        size += fields_[i].size * sizeof(GLfloat);

    return size;
}

void erase(PolyData *poly_data_ptr) {
    glDeleteBuffers(poly_data_ptr->vbo_size_, poly_data_ptr->vbo_);
}


