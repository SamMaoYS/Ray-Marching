//
// Created by sam on 2020-07-18.
//

#include "io.h"

using namespace io;

bool io::first_mouse = true;
glm::dvec2 io::mouse_pos_old = glm::dvec2();
glm::dvec2 io::mouse_pos_new = glm::dvec2();
glm::dvec2 io::mouse_offset = glm::dvec2();
glm::dvec2 io::scroll_offset = glm::dvec2();
float io::time_delta = 0.0f;
float io::time_old = 0.0f;

void io::mouseCallBack(GLFWwindow *gl_window, double x, double y) {
    if (first_mouse)
    {
        mouse_pos_old = glm::dvec2(x, y);
        mouse_pos_new = mouse_pos_old;
        first_mouse = false;
    }

    mouse_pos_new = glm::dvec2(x, y);
    mouse_offset = mouse_pos_new - mouse_pos_old;

    mouse_pos_old = mouse_pos_new;
}

void io::scrollCallBack(GLFWwindow *gl_window, double x_offset, double y_offset) {
    scroll_offset = glm::dvec2(x_offset, y_offset);
}
