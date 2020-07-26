//
// Created by sam on 2020-07-21.
//

#include "actor.h"

class PolyData;

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
    bind(poly_data_ptr_);
    VertexFieldVector fields = poly_data_ptr_->fields();
    for (int i = 0; i < fields.size(); ++i) {
        glVertexAttribPointer(fields[i].pos, fields[i].size, fields[i].type, fields[i].normalize, poly_data_ptr->fieldSize(), (void*)fields[i].offset);
        glEnableVertexAttribArray(i);
    }
    // Unbind VAO
    glEnableVertexAttribArray(0);
}

void Actor::setShader(Shader *shader_ptr) {
    shader_ptr_ = shader_ptr;
}

void Actor::setDrawParams(GLenum method, GLint first, GLsizei count) {
    method_ = method;
    first_ = first;
    count_ = count;
}

void draw(Actor *actor_ptr) {
    actor_ptr->shader_ptr_->use();
    actor_ptr->shader_ptr_->setMat4("projection", actor_ptr->projection_);
    actor_ptr->shader_ptr_->setMat4("view", actor_ptr->view_);
    actor_ptr->shader_ptr_->setMat4("model", actor_ptr->model_);
    actor_ptr->shader_ptr_->setVec3("lightPos", actor_ptr->light_pos_);
    actor_ptr->shader_ptr_->setVec3("lightColor", actor_ptr->light_color_);
    actor_ptr->shader_ptr_->setVec3("viewPos", actor_ptr->view_pos_);
    glBindVertexArray(*(actor_ptr->vao_));
    glDrawArrays(actor_ptr->method_, actor_ptr->first_, actor_ptr->count_);
}

void erase(Actor *actor_ptr) {
    glDeleteVertexArrays(actor_ptr->vao_size_, actor_ptr->vao_);
    erase(actor_ptr->poly_data_ptr_);
}