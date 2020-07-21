//
// Created by sam on 2020-07-18.
//

#ifndef SDF_CAMERA_H
#define SDF_CAMERA_H


#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

enum MoveDirection {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

// Default camera values
const GLfloat PITCH       =  0.0f;
const GLfloat YAW         = -90.0f;
const GLfloat SPEED       =  2.5f;
const GLfloat SENSITIVITY =  0.1f;
const GLfloat ZOOM        =  45.0f;

class Camera {
public:
    Camera(const std::string &name = "camera0");
    explicit Camera(glm::vec3 pos, glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), GLfloat pitch = PITCH, GLfloat yaw = YAW, const std::string &name = "camera0");
    ~Camera() = default;

    void moveCamera(MoveDirection dir, GLfloat deltaTime);
    void rotateCamera(GLfloat xOffset, GLfloat yOffset);
    void zoomCamera(GLfloat scroll);

    void setCameraPos(glm::vec3 pos);
    void setCameraFront(glm::vec3 front);
    void setCameraUP(glm::vec3 up);
    void setCameraYaw(GLfloat yaw);
    void setCameraPitch(GLfloat pitch);
    void setMoveSpeed(GLfloat speed);
    void setMouseSensitivity(GLfloat sensitivity);
    void setCameraZoom(GLfloat zoom);

    glm::mat4 getViewMatrix() const;
    inline glm::vec3 getCameraPos() const {return this->cam_pos_;}
    inline glm::vec3 getCameraFront() const {return this->cam_front_;}
    inline glm::vec3 getCameraUP() const {return this->cam_up_;}
    inline glm::vec3 getCameraRight() const {return this->cam_right_;}
    inline GLfloat getCameraYaw() const {return this->cam_yaw_;}
    inline GLfloat getCameraPitch() const {return this->cam_pitch_;}
    inline GLfloat getMoveSpeed() const {return this->move_speed_;}\
    inline GLfloat getMouseSensitivity() const {return this->mouse_sensitivity_;}
    inline GLfloat getCameraZoom() const {return this->cam_zoom_;}

private:
    glm::vec3 cam_pos_;
    glm::vec3 cam_front_;
    glm::vec3 cam_up_;
    glm::vec3 cam_right_;
    glm::vec3 world_up_;
    // Euler Angles
    GLfloat cam_pitch_;
    GLfloat cam_yaw_;
    // Move options
    GLfloat move_speed_;
    GLfloat mouse_sensitivity_;
    GLfloat cam_zoom_;

    std::string name_;

    void updateCameraVectors();
};


#endif //SDF_CAMERA_H
