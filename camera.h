

#ifndef OPENGL_PRACTICE_CAMERA_H
#define OPENGL_PRACTICE_CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>


class Camera {

public:
    Camera();

    Camera(glm::vec3 in_position, glm::vec3 in_up, GLfloat in_yaw, GLfloat in_pitch, GLfloat in_movement_speed,
           GLfloat in_rotation_speed);

    ~Camera();

    void KeyControl(bool *keys, GLfloat delta_time);

    void MouseControl(GLfloat x_delta, GLfloat y_delta);

    glm::mat4 CalculateViewMatrix();

private:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 world_up;

    GLfloat yaw;
    GLfloat pitch;

    GLfloat movement_speed;
    GLfloat rotation_speed;

    void update();
};


#endif //OPENGL_PRACTICE_CAMERA_H
