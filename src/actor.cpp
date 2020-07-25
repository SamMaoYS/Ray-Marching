//
// Created by sam on 2020-07-21.
//

#include "actor.h"

Actor::Actor() {
    vao_ = new GLuint;
    vao_size_ = 1;
    glGenVertexArrays(vao_size_, vao_);
}

Actor::Actor(GLsizei size) {
    vao_ = new GLuint;
    vao_size_ = size;
    glGenVertexArrays(vao_size_, vao_);
}

Actor::~Actor() {
    glDeleteBuffers(vao_size_, vao_);
}

void Actor::setPolyData(PolyData *poly_data_ptr) {
    poly_data_ptr_ = poly_data_ptr;
    glBindVertexArray(*vao_);
    poly_data_ptr_->bind();
    VertexFieldVector fields = poly_data_ptr_->fields();
    for (int i = 0; i < fields.size(); ++i) {
        glVertexAttribPointer(fields[i].pos, fields[i].size, fields[i].type, fields[i].normalize, poly_data_ptr->fieldSize(), (void*)fields[i].offset);
        glEnableVertexAttribArray(i);
    }
    // Unbind VAO
    glEnableVertexAttribArray(0);
}

void Actor::bind() {
    glBindVertexArray(*vao_);
}

void Actor::erase() {
    glDeleteVertexArrays(vao_size_, vao_);
}

