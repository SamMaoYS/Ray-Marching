//
// Created by sam on 2020-07-29.
//

#include "light.h"

void Light::bind(Shader *shader_ptr) {
    shader_ptr->setUniform(uniform_name_+"["+std::to_string(index_)+"].ambient", ambient_);
    shader_ptr->setUniform(uniform_name_+"["+std::to_string(index_)+"].diffuse", diffuse_);
    shader_ptr->setUniform(uniform_name_+"["+std::to_string(index_)+"].specular", specular_);
    shader_ptr->setUniform(uniform_name_+"["+std::to_string(index_)+"].color", color_);
}

void DirLight::bind(Shader *shader_ptr) {
    Light::bind(shader_ptr);
    shader_ptr->setUniform(uniform_name_+"["+std::to_string(index_)+"].direction", direction_);
}

void PointLight::bind(Shader *shader_ptr) {
    Light::bind(shader_ptr);
    shader_ptr->setUniform(uniform_name_+"["+std::to_string(index_)+"].position", position_);
    shader_ptr->setUniform(uniform_name_+"["+std::to_string(index_)+"].constant", constant_);
    shader_ptr->setUniform(uniform_name_+"["+std::to_string(index_)+"].linear", linear_);
    shader_ptr->setUniform(uniform_name_+"["+std::to_string(index_)+"].quadratic", quadratic_);
}

void SpotLight::bind(Shader *shader_ptr) {
    Light::bind(shader_ptr);
    shader_ptr->setUniform(uniform_name_+"["+std::to_string(index_)+"].direction", direction_);
    shader_ptr->setUniform(uniform_name_+"["+std::to_string(index_)+"].position", position_);
    shader_ptr->setUniform(uniform_name_+"["+std::to_string(index_)+"].constant", constant_);
    shader_ptr->setUniform(uniform_name_+"["+std::to_string(index_)+"].linear", linear_);
    shader_ptr->setUniform(uniform_name_+"["+std::to_string(index_)+"].quadratic", quadratic_);
    shader_ptr->setUniform(uniform_name_+"["+std::to_string(index_)+"].cutOff", cut_off_);
    shader_ptr->setUniform(uniform_name_+"["+std::to_string(index_)+"].outerCutOff", outer_cut_off_);
}
