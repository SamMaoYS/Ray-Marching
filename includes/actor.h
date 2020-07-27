//
// Created by sam on 2020-07-21.
//

#ifndef SDF_ACTOR_H
#define SDF_ACTOR_H


#include <iostream>
#include <Eigen/Dense>
#include "shader.h"
#include "poly_data.h"

struct Light {
    Light()
            : ambient(glm::vec3(1.0)), diffuse(glm::vec3(1.0)), specular(glm::vec3(5.0)), pos(glm::vec3(0.0)),
              color(glm::vec3(1.0)) {}

    Light(glm::vec3 in_ambient, glm::vec3 in_diffuse, glm::vec3 in_specular, glm::vec3 in_pos, glm::vec3 in_color)
            : ambient(in_ambient), diffuse(in_diffuse), specular(in_specular), pos(in_pos), color(in_color) {}

    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    glm::vec3 pos;
    glm::vec3 color;
};

struct Material {
    Material() : diffuse_texture(0), specular_texture(0), shininess(64.0) {}

    Material(GLuint in_diffuse_tex, GLuint in_specular_tex, GLfloat in_shininess)
            : diffuse_texture(in_diffuse_tex),
              specular_texture(in_specular_tex),
              shininess(in_shininess) {}

    GLuint diffuse_texture;
    GLuint specular_texture;
    GLfloat shininess;
};

class Actor {
public:
    Actor();

    Actor(GLsizei size);

    ~Actor();

    void setPolyData(PolyData *poly_data_ptr);

    void setShader(Shader *shader_ptr);

    inline void setProjectionMatrix(const glm::mat4 &projection) { projection_ = projection; }

    inline void setViewMatrix(const glm::mat4 &view) { view_ = view; }

    inline void setModelMatrix(const glm::mat4 &model) { model_ = model; }

    inline void setLight(const Light &light) { light_ = light; }

    inline void setLightAmbient(glm::vec3 in_ambient) { light_.ambient = in_ambient; }

    inline void setLightDiffuse(glm::vec3 in_diffuse) { light_.diffuse = in_diffuse; }

    inline void setLightSpecular(glm::vec3 in_specular) { light_.specular = in_specular; }

    inline void setLightPos(glm::vec3 in_pos) { light_.pos = in_pos; }

    inline void setLightColor(glm::vec3 in_color) { light_.color = in_color; }

    inline void setViewPos(const glm::vec3 &view_pos) { view_pos_ = view_pos; }

    void setDrawParams(GLenum method, GLint first, GLsizei count);

    void loadDiffuseTexture(const std::string &path);

    void loadSpecularTexture(const std::string &path);

protected:
    friend void init(Actor *actor_ptr);

    friend void draw(Actor *actor_ptr);

    friend void erase(Actor *actor_ptr);

    GLuint loadTexture(const std::string &path);

private:
    PolyData *poly_data_ptr_;
    Shader *shader_ptr_;
    GLuint *vao_;
    GLsizei vao_size_;

    glm::mat4 projection_;
    glm::mat4 view_;
    glm::mat4 model_;
    glm::vec3 view_pos_;

    Light light_;
    Material material_;

    GLenum method_;
    GLint first_;
    GLsizei count_;
};


#endif //SDF_ACTOR_H
