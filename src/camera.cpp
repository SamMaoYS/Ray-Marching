//
// Created by sam on 2020-07-18.
//

#include "camera.h"

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(const std::string &name) {
    cam_pos_ = glm::vec3(0.0f, 0.0f, 3.0f);
    cam_up_ = glm::vec3(0.0f, 1.0f, 0.0f);
    cam_right_ = glm::vec3(1.0f, 0.0f, 0.0f);
    cam_front_ = glm::vec3(0.0f, 0.0f, -1.0f);
    world_up_ = this->cam_up_;
    cam_pitch_ = PITCH;
    cam_yaw_ = YAW;
    move_speed_ = SPEED;
    mouse_sensitivity_ = SENSITIVITY;
    cam_zoom_ = ZOOM;
    name_ = name;
    updateCameraVectors();
}

Camera::Camera(glm::vec3 pos, glm::vec3 up, GLfloat pitch, GLfloat yaw, const std::string &name) {
    cam_pos_ = pos;
    cam_up_ = up;
    cam_right_ = glm::vec3(1.0f, 0.0f, 0.0f);
    cam_front_ = glm::vec3(0.0f, 0.0f, -1.0f);;
    world_up_ = this->cam_up_;
    cam_pitch_ = pitch;
    cam_yaw_ = yaw;
    move_speed_ = SPEED;
    mouse_sensitivity_ = SENSITIVITY;
    cam_zoom_ = ZOOM;
    name_ = name;
    updateCameraVectors();
}

void Camera::moveCamera(MoveDirection dir, GLfloat deltaTime) {
    GLfloat displacement = this->move_speed_ * deltaTime;
    if (dir == FORWARD) {
        this->cam_pos_ += this->cam_front_ * displacement;
    }
    if (dir == BACKWARD) {
        this->cam_pos_ -= this->cam_front_ * displacement;
    }
    if (dir == LEFT) {
        this->cam_pos_ -= this->cam_right_ * displacement;
    }
    if (dir == RIGHT) {
        this->cam_pos_ += this->cam_right_ * displacement;
    }
}

void Camera::rotateCamera(GLfloat x_offset, GLfloat y_offset) {
    x_offset *= this->mouse_sensitivity_;
    y_offset *= this->mouse_sensitivity_;

    this->cam_pitch_ -= x_offset;
    this->cam_yaw_ += y_offset;

    if (this->cam_pitch_ > 89.0f) {
        this->cam_pitch_ = 89.0f;
    }
    if (this->cam_pitch_ < -89.0f) {
        this->cam_pitch_ = -89.0f;
    }

    updateCameraVectors();
}

void Camera::zoomCamera(GLfloat scroll) {
    if (this->cam_zoom_ >= 44.1f && this->cam_zoom_ <= 45.9f) {
        this->cam_zoom_ -= 0.1f*scroll;
    }
    if (this->cam_zoom_ <= 44.1f) {
        this->cam_zoom_ = 44.1f;
    }
    if (this->cam_zoom_ >= 45.9f) {
        this->cam_zoom_ = 45.9f;
    }
}

void Camera::setCameraPos(glm::vec3 pos) {
    this->cam_pos_ = pos;
}

void Camera::setCameraFront(glm::vec3 front) {
    this->cam_front_ = front;
}
void Camera::setCameraUP(glm::vec3 up) {
    this->cam_up_ = up;
}

void Camera::setCameraYaw(GLfloat yaw) {
    this->cam_yaw_ = yaw;
    updateCameraVectors();
}

void Camera::setCameraPitch(GLfloat pitch) {
    this->cam_pitch_ = pitch;
    updateCameraVectors();
}

void Camera::setMoveSpeed(GLfloat speed) {
    this->move_speed_ = speed;
}

void Camera::setMouseSensitivity(GLfloat sensitivity) {
    this->mouse_sensitivity_ = sensitivity;
}

void Camera::setCameraZoom(GLfloat zoom) {
    this->cam_zoom_ = zoom;
}

glm::mat4 Camera::getViewMatrix() const {
    return glm::lookAt(this->cam_pos_, this->cam_pos_ + this->cam_front_, this->cam_up_);
}

void Camera::updateCameraVectors() {
    glm::vec3 front;
    front.x = cos(glm::radians(this->cam_pitch_)) * cos(glm::radians(this->cam_yaw_));
    front.y = sin(glm::radians(this->cam_pitch_));
    front.z = cos(glm::radians(this->cam_pitch_)) * sin(glm::radians(this->cam_yaw_));
    this->cam_front_ = glm::normalize(front);
    this->cam_right_ = glm::normalize(glm::cross(this->cam_front_, this->world_up_));
    this->cam_up_ = glm::normalize(glm::cross(this->cam_right_, this->cam_front_));
}