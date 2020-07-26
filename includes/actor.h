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
    void setShader(Shader *shader_ptr);

    inline void setProjectionMatrix(const glm::mat4 &projection) {projection_ = projection;}
    inline void setViewMatrix(const glm::mat4 &view) {view_ = view;}
    inline void setModelMatrix(const glm::mat4 &model) {model_ = model;}
    inline void setLightPos(const glm::vec3 &light_pos) {light_pos_ = light_pos;}
    inline void setLightColor(const glm::vec3 &light_color) {light_color_ = light_color;}
    inline void setViewPos(const glm::vec3 &view_pos) {view_pos_ = view_pos;}
    void setDrawParams(GLenum method, GLint first, GLsizei count);

protected:
    friend void draw(Actor *actor_ptr);
    friend void erase(Actor *actor_ptr);

private:
    PolyData *poly_data_ptr_;
    Shader* shader_ptr_;
    GLuint *vao_;
    GLsizei vao_size_;

    glm::mat4 projection_;
    glm::mat4 view_;
    glm::mat4 model_;
    glm::vec3 light_pos_;
    glm::vec3 light_color_;
    glm::vec3 view_pos_;

    GLenum method_;
    GLint first_;
    GLsizei count_;
};


#endif //SDF_ACTOR_H
