//
// Created by sam on 2020-07-18.
//

#include "interactor.h"
#include "io.h"
#include "actor.h"
#include "shader.h"
#include <glm/gtc/matrix_transform.hpp>

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

    Shader light_shader("../shaders/light.vs", "../shaders/light.frag");
    Shader cube_shader("../shaders/model.vs", "../shaders/model.frag");

    PolyData* cube_ptr = new PolyData();
    cube_ptr->genCube();

    Actor* cube_actor = new Actor();
    cube_actor->setPolyData(cube_ptr);

    Actor light_actor;
    light_actor.setPolyData(cube_ptr);

    glm::vec3 light_pos(1.2f, 1.0f, 2.0f);

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

        cube_shader.use();
        cube_shader.setVec3("lightColor", 1.0, 1.0, 1.0);
        cube_shader.setVec3("lightPos", light_pos);
        cube_shader.setVec3("viewPos", current_camera_->getCameraPos());
        cube_shader.setMat4("projection", projection);
        cube_shader.setMat4("view", view);
        glm::mat4 model = glm::mat4(1.0f);
        cube_shader.setMat4("model", model);

        cube_actor->bind();
        glDrawArrays(GL_TRIANGLES, 0, 36);

        light_shader.use();
        light_shader.setMat4("projection", projection);
        light_shader.setMat4("view", view);
        model = glm::mat4(1.0f);
        model = glm::translate(model, light_pos);
        model = glm::scale(model, glm::vec3(0.2f));
        light_shader.setMat4("model", model);
        light_shader.setVec3("lightColor", 1.0, 1.0, 1.0);

        light_actor.bind();
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // swap buffers and poll IO events
        glfwSwapBuffers(gl_window);
        glfwPollEvents();
    }

    cube_actor->erase();
    light_actor.erase();
    cube_ptr->erase();

    glfwTerminate();
}

