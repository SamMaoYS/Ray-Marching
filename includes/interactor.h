//
// Created by sam on 2020-07-18.
//

#ifndef SDF_INTERACTOR_H
#define SDF_INTERACTOR_H


#include "window.h"
#include "camera.h"
#include <vector>

class Interactor {
public:
    Interactor(Window* window, Camera* camera);
    ~Interactor();

    void render();

    void setCurrentCamera(Camera* camera);

    inline Window *getWindowPtr() const {return window_;}
    inline const Window *getWindowConstPtr() const {return window_;}

protected:
    bool initialize();
    void keyCallBack(GLFWwindow *gl_window);

private:
    Window *window_;
    Camera *current_camera_;

    int width_;
    int height_;

    bool status_;
};


#endif //SDF_INTERACTOR_H
