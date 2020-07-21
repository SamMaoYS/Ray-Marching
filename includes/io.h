//
// Created by sam on 2020-07-18.
//

#ifndef SDF_IO_H
#define SDF_IO_H


#include <iostream>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// GLM
#include <glm/glm.hpp>

namespace io {
    extern bool first_mouse;
    extern glm::dvec2 mouse_pos_old;
    extern glm::dvec2 mouse_pos_new;
    extern glm::dvec2 mouse_offset;
    extern glm::dvec2 scroll_offset;

    extern float time_delta;
    extern float time_old;

    extern void mouseCallBack(GLFWwindow *gl_window, double x, double y);
    extern void scrollCallBack(GLFWwindow *gl_window, double x_offset, double y_offset);
};


#endif //SDF_IO_H
