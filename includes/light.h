//
// Created by sam on 2020-07-29.
//

#ifndef SDF_LIGHT_H
#define SDF_LIGHT_H


#include <iostream>

#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif

#include <GL/glew.h>

#include <glm/glm.hpp>

#include "shader.h"

class Light {
public:
    Light() : ambient_(glm::vec3(1.0)), diffuse_(glm::vec3(1.0)), specular_(glm::vec3(5.0)),
              color_(glm::vec3(1.0)) {}

    Light(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 color)
            : ambient_(ambient), diffuse_(diffuse), specular_(specular), color_(color) {}

    ~Light() = default;

    virtual void bind(Shader *shader_ptr);

    inline void setUniformName(const std::string &name) {uniform_name_ = name;}
    inline std::string getUniformName() const {return uniform_name_;}

    inline void setIndex(int index) {index_ = index;}
    inline int getIndex() const {return index_;}

    inline void setAmbient(glm::vec3 ambient) { ambient_ = ambient; }

    inline void setDiffuse(glm::vec3 diffuse) { diffuse_ = diffuse; }

    inline void setSpecular(glm::vec3 specular) { specular_ = specular; }

    inline void setColor(glm::vec3 color) { color_ = color; }

    inline glm::vec3 getAmbient() const { return ambient_; }

    inline glm::vec3 getDiffuse() const { return diffuse_; }

    inline glm::vec3 getSpecular() const { return specular_; }

    inline glm::vec3 getColor() const { return color_; }

protected:
    glm::vec3 ambient_;
    glm::vec3 diffuse_;
    glm::vec3 specular_;
    glm::vec3 color_;

    std::string uniform_name_;
    int index_;
};

class DirLight : public Light {
public:
    DirLight() : Light(), direction_(glm::vec3(0, 0, -1)) {uniform_name_ = "dirLights";}

    ~DirLight() = default;

    void bind(Shader *shader_ptr);

    inline void setDirection(glm::vec3 direction) { direction_ = direction; }

    inline glm::vec3 getDirection() const { return direction_; }

private:
    glm::vec3 direction_;
};

class PointLight : public Light {
public:
    PointLight() : Light(), position_(glm::vec3(0, 2, 1)), constant_(1.0f), linear_(0.09f), quadratic_(0.032f) { uniform_name_ = "pointLights";}

    ~PointLight() = default;

    void bind(Shader *shader_ptr);

    inline void setPosition(glm::vec3 position) { position_ = position; }

    inline void setConstant(float constant) { constant_ = constant; }

    inline void setLinear(float linear) { linear_ = linear; }

    inline void setQuadratic(float quadratic) { quadratic_ = quadratic; }

    inline glm::vec3 getPosition() const { return position_; }

    inline float getConstant() const { return constant_; }

    inline float getLinear() const { return linear_; }

    inline float getQuadratic() const { return quadratic_; }

private:
    glm::vec3 position_;
    float constant_;
    float linear_;
    float quadratic_;
};

class SpotLight : public Light {
public:
    SpotLight()
            : Light(), direction_(glm::vec3(0, 0, -1)), position_(glm::vec3(0, 2, 1)), constant_(1.0f), linear_(0.09f),
              quadratic_(0.032f), cut_off_(glm::cos(glm::radians(12.5f))),
              outer_cut_off_(glm::cos(glm::radians(15.0f))) {}

    ~SpotLight() = default;

    void bind(Shader *shader_ptr);

    inline void setDirection(glm::vec3 direction) { direction_ = direction; }

    inline void setPosition(glm::vec3 position) { position_ = position; }

    inline void setConstant(float constant) { constant_ = constant; }

    inline void setLinear(float linear) { linear_ = linear; }

    inline void setQuadratic(float quadratic) { quadratic_ = quadratic; }

    inline void setCutOff(float cut_off) { cut_off_ = cut_off; }

    inline void setOuterCutOff(float outer_cut_off) { outer_cut_off_ = outer_cut_off; }

    inline glm::vec3 getDirection() const { return direction_; }

    inline glm::vec3 getPosition() const { return position_; }

    inline float getConstant() const { return constant_; }

    inline float getLinear() const { return linear_; }

    inline float getQuadratic() const { return quadratic_; }

    inline float getCutOff() const { return cut_off_; }

    inline float getOuterCutOff() const { return outer_cut_off_; }

private:
    glm::vec3 direction_;
    glm::vec3 position_;
    float constant_;
    float linear_;
    float quadratic_;
    float cut_off_;
    float outer_cut_off_;
};


#endif //SDF_LIGHT_H
