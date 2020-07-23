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
    glfwSetInputMode(window_->getGLWindowPtr(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
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
    Actor act;
    Mat36_12f cube = act.genCube();

    Shader light_shader("../shaders/light.vs", "../shaders/light.frag");
    Shader cube_shader("../shaders/model.vs", "../shaders/model.frag");

    unsigned int VBO, cubeVAO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*cube.size(), cube.data(), GL_STATIC_DRAW);

    glBindVertexArray(cubeVAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 12 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 12 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 12 * sizeof(float), (void*)(7 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 12 * sizeof(float), (void*)(10 * sizeof(float)));
    glEnableVertexAttribArray(3);

    unsigned int lightVAO;
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 12 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

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

        glBindVertexArray(cubeVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // swap buffers and poll IO events
        glfwSwapBuffers(gl_window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteVertexArrays(1, &lightVAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
}

