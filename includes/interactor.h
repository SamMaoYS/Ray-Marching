//
// Created by sam on 2020-07-18.
//

#ifndef SDF_INTERACTOR_H
#define SDF_INTERACTOR_H


#include "window.h"
#include "camera.h"
#include "actor.h"
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Interactor {
public:
    Interactor(Window* window, Camera* camera);
    ~Interactor() = default;

    void render();
    void addActor(Actor* actor);

    void setCurrentCamera(Camera* camera);

    inline Window *getWindowPtr() const {return window_;}
    inline const Window *getWindowConstPtr() const {return window_;}

protected:
    bool initialize();
    void keyCallBack(GLFWwindow *gl_window);

private:
    Window *window_;
    Camera *current_camera_;
    std::vector<Actor*> actor_ptr_vec_;

    int width_;
    int height_;

    bool status_;
};


#endif //SDF_INTERACTOR_H
