//
// Created by sam on 2020-07-18.
//

#include "window.h"

Window::Window() {
    name_ = "GLFW Window";
    width_ = 640;
    height_ = 480;
    this->create();
}

Window::Window(const std::string &name) {
    name_ = name;
    width_ = 640;
    height_ = 480;
    this->create();
}

Window::Window(const std::string &name, const int width, const int height) {
    name_ = name;
    width_ = width;
    height_ = height;
    this->create();
}

Window::~Window() {
    glfwDestroyWindow(gl_window_);
}

void Window::setBackGroundColor(GLclampf rgba[4]) {
    setBackGroundColor(rgba[0], rgba[1], rgba[2], rgba[3]);
}

void Window::setBackGroundColor(GLclampf r, GLclampf g, GLclampf b, GLclampf a) {
    background_color_[0] = r;
    background_color_[1] = g;
    background_color_[2] = b;
    background_color_[3] = a;
}

void Window::create() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    status_ = true;
    gl_window_ = nullptr;

    gl_window_ = glfwCreateWindow(width_, height_, name_.c_str(), nullptr, nullptr);
    if (gl_window_ == nullptr)
    {
        status_ = false;
        throw std::invalid_argument("Failed to create GLFW window");
        glfwTerminate();
    }
    glfwMakeContextCurrent(gl_window_);
    glfwSetFramebufferSizeCallback(gl_window_,[](GLFWwindow *window, int width, int height) { glViewport(0, 0, width, height); });

    if (glewInit() != GLEW_OK) {
        status_ = false;
        throw std::invalid_argument("Failed to initialize GLEW");
    }

    std::fill_n(background_color_, 4, 0);
}
