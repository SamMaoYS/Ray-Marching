//
// Created by sam on 2020-07-18.
//

#include "interactor.h"
#include "io.h"
#include "shader.h"
#include <glm/gtc/matrix_transform.hpp>

class Actor;

Interactor::Interactor(Window *window, Camera* camera) {
    window_ = window;
    current_camera_ = camera;
}

void Interactor::setCurrentCamera(Camera* camera) {
    current_camera_ = camera;
}

bool Interactor::initialize() {
    glEnable(GL_DEPTH_TEST);

    glfwSetCursorPosCallback(window_->getGLWindowPtr(), io::mouseCallBack);
    glfwSetScrollCallback(window_->getGLWindowPtr(), io::scrollCallBack);
//    glfwSetInputMode(window_->getGLWindowPtr(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    return false;
}

void Interactor::keyCallBack(GLFWwindow *gl_window) {
    if (glfwGetKey(gl_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(gl_window, true);

    if (glfwGetKey(gl_window, GLFW_KEY_W) == GLFW_PRESS)
        current_camera_->moveCamera(FORWARD, io::time_delta);
    if (glfwGetKey(gl_window, GLFW_KEY_S) == GLFW_PRESS)
        current_camera_->moveCamera(BACKWARD, io::time_delta);
    if (glfwGetKey(gl_window, GLFW_KEY_A) == GLFW_PRESS)
        current_camera_->moveCamera(LEFT, io::time_delta);
    if (glfwGetKey(gl_window, GLFW_KEY_D) == GLFW_PRESS)
        current_camera_->moveCamera(RIGHT, io::time_delta);
}

void Interactor::render() {
    initialize();

    GLFWwindow *gl_window = window_->getGLWindowPtr();
    window_->getSize(width_, height_);

    while (!glfwWindowShouldClose(gl_window)) {
        float current_time = glfwGetTime();
        io::time_delta = current_time - io::time_old;
        io::time_old = current_time;

        keyCallBack(gl_window);

        // Update camera
        current_camera_->rotateCamera(io::mouse_offset.y, io::mouse_offset.x);
        current_camera_->zoomCamera(io::scroll_offset.y);
        io::mouse_offset.x = 0, io::mouse_offset.y = 0;
        io::scroll_offset.x = 0, io::scroll_offset.y = 0;

        glClearColor(window_->getBackGroundColor()[0], window_->getBackGroundColor()[1], window_->getBackGroundColor()[2], window_->getBackGroundColor()[3]);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 projection = glm::perspective(glm::radians(current_camera_->getCameraZoom()), (float)width_ / (float)height_, 0.1f, 100.0f);
        glm::mat4 view = current_camera_->getViewMatrix();

        for (Actor *actor_ptr_ : actor_ptr_vec_) {
            actor_ptr_->setProjectionMatrix(projection);
            actor_ptr_->setViewMatrix(view);
            actor_ptr_->setViewPos(current_camera_->getCameraPos());
            draw(actor_ptr_);
        }

        // swap buffers and poll IO events
        glfwSwapBuffers(gl_window);
        glfwPollEvents();
    }

    for (Actor *actor_ptr_ : actor_ptr_vec_)
        erase(actor_ptr_);

    glfwTerminate();
}

void Interactor::addActor(Actor* actor) {
    actor_ptr_vec_.push_back(actor);
}
