//
// Created by sam on 2020-07-18.
//

#ifndef SDF_WINDOW_H
#define SDF_WINDOW_H


#include <iostream>

// GLEW
#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

class Window {
public:
    Window();
    explicit Window(const std::string &name);
    Window(const std::string &name, int width, int height);
    ~Window();

    void setBackGroundColor(GLclampf rgba[3]);
    void setBackGroundColor(GLclampf r, GLclampf g, GLclampf b, GLclampf a);

    inline std::string getName() const {return name_;}
    inline bool getStatus() const {return status_;}
    inline void getSize(int &width, int &height) const {width = width_, height = height_;}
    inline const GLclampf* getBackGroundColor() const { return background_color_;}

    inline GLFWwindow *getGLWindowPtr() const {return gl_window_;}
    inline const GLFWwindow *getGLWindowConstPtr() const {return gl_window_;}

protected:
    void create();

private:
    GLFWwindow *gl_window_;
    std::string name_;
    int width_;
    int height_;
    bool status_;
    GLclampf background_color_[4];
};


#endif //SDF_WINDOW_H
