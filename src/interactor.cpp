//
// Created by sam on 2020-07-18.
//

#include "interactor.h"
#include "io.h"

Interactor::Interactor(Window *window, Camera* camera) {
    window_ = window;
    current_camera_ = camera;
}

Interactor::~Interactor() {

}

void Interactor::setCurrentCamera(Camera* camera) {
    current_camera_ = camera;
}

bool Interactor::initialize() {
    glEnable(GL_DEPTH_TEST);

    glfwSetCursorPosCallback(window_->getGLWindowPtr(), io::mouseCallBack);
    glfwSetScrollCallback(window_->getGLWindowPtr(), io::scrollCallBack);

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
    GLFWwindow *gl_window = window_->getGLWindowPtr();
    while (!glfwWindowShouldClose(gl_window)) {
        keyCallBack(gl_window);

        glClearColor(window_->getBackGroundColor()[0], window_->getBackGroundColor()[1], window_->getBackGroundColor()[2], window_->getBackGroundColor()[3]);
        glClear(GL_COLOR_BUFFER_BIT);

        // swap buffers and poll IO events
        glfwSwapBuffers(gl_window);
        glfwPollEvents();
    }
}

