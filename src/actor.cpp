//
// Created by sam on 2020-07-21.
//

#include "actor.h"
#include "stb_image.h"

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

GLuint Actor::loadTexture(const std::string &path) {
    GLuint texture_id;
    glGenTextures(1, &texture_id);

    int width, height, channel;
    unsigned char *data = stbi_load(path.c_str(), &width, &height, &channel, 0);
    if (data) {
        GLenum format;
        if (channel == 1)
            format = GL_RED;
        else if (channel == 3)
            format = GL_RGB;
        else if (channel == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, texture_id);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else {
        std::cerr << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return texture_id;
}

void Actor::loadDiffuseTexture(const std::string &path) {
    material_.diffuse_texture = loadTexture(path);
}

void Actor::loadSpecularTexture(const std::string &path) {
    material_.specular_texture = loadTexture(path);
}

void init(Actor *actor_ptr) {
    actor_ptr->shader_ptr_->use();
    actor_ptr->shader_ptr_->setInt("material.diffuse", 0);
    actor_ptr->shader_ptr_->setInt("material.specular", 1);
}

void draw(Actor *actor_ptr) {
    actor_ptr->shader_ptr_->use();
    actor_ptr->shader_ptr_->setMat4("projection", actor_ptr->projection_);
    actor_ptr->shader_ptr_->setMat4("view", actor_ptr->view_);
    actor_ptr->shader_ptr_->setMat4("model", actor_ptr->model_);
    actor_ptr->shader_ptr_->setVec3("light.pos", actor_ptr->light_.pos);
    actor_ptr->shader_ptr_->setVec3("light.color", actor_ptr->light_.color);
    actor_ptr->shader_ptr_->setVec3("light.ambient", actor_ptr->light_.ambient);
    actor_ptr->shader_ptr_->setVec3("light.diffuse", actor_ptr->light_.diffuse);
    actor_ptr->shader_ptr_->setVec3("light.specular", actor_ptr->light_.specular);
    actor_ptr->shader_ptr_->setVec3("viewPos", actor_ptr->view_pos_);
    actor_ptr->shader_ptr_->setFloat("material.shininess", actor_ptr->material_.shininess);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, actor_ptr->material_.diffuse_texture);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, actor_ptr->material_.specular_texture);

    glBindVertexArray(*(actor_ptr->vao_));
    glDrawArrays(actor_ptr->method_, actor_ptr->first_, actor_ptr->count_);
}

void erase(Actor *actor_ptr) {
    glDeleteVertexArrays(actor_ptr->vao_size_, actor_ptr->vao_);
    erase(actor_ptr->poly_data_ptr_);
}

