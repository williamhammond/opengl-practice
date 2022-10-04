

#include "camera.h"
#include "GLFW/glfw3.h"

Camera::Camera() : Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, 0.0f, 5.0f, 1.0f) {

}

Camera::Camera(glm::vec3 in_position, glm::vec3 in_up, GLfloat in_yaw, GLfloat in_pitch, GLfloat in_movement_speed,
               GLfloat in_rotation_speed) {
    position = in_position;
    world_up = in_up;
    yaw = in_yaw;
    pitch = in_pitch;

    front = glm::vec3(0.0f, 0.0f, -1.0f);
    movement_speed = in_movement_speed;
    rotation_speed = in_rotation_speed;

    update();
}

Camera::~Camera() {

}

void Camera::update() {
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(front);

    right = glm::normalize(glm::cross(front, world_up));
    up = glm::normalize(glm::cross(right, front));
}

void Camera::KeyControl(bool *keys) {
    if (keys[GLFW_KEY_W]) {
        position += front * movement_speed;
    }

    if (keys[GLFW_KEY_A]) {
        position -= right * movement_speed;
    }

    if (keys[GLFW_KEY_S]) {
        position -= front * movement_speed;
    }

    if (keys[GLFW_KEY_D]) {
        position += right * movement_speed;
    }
}

glm::mat4 Camera::CalculateViewMatrix() {
    return glm::lookAt(position, position + front, up);
}
