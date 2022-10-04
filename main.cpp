#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "mesh.h"
#include "shader.h"
#include "window.h"
#include "camera.h"

std::vector<Mesh *> meshes;

bool direction = true;
float tri_offset = 0.0f;
float tri_max_offset = 0.7f;
float tri_increment = 0.0005f;

float current_angle = 0.0f;
float angle_delta = 0.001f;


void CreateTriangle() {
    unsigned int indices[] = {
            0, 3, 1,
            1, 3, 2,
            2, 3, 0,
            0, 1, 2
    };

    GLfloat vertices[] = {
            -1.0f, -1.0f, 0.0f,
            0.0f, -1.0f, 1.0f,
            1.0f, -1.0f, 0.0f,
            0.0f, 1.0f, 0.0f
    };

    Mesh *mesh = new Mesh();
    mesh->CreateMesh(vertices, indices, 12, 12);
    meshes.push_back(mesh);
}

Shader *CreateShader() {
    auto *result = new Shader();
    result->CreateFromFile("../vertex.glsl", "../fragment.glsl");
    return result;
}

int main() {
    auto *window = new Window(800, 600);
    window->Initalize();

    CreateTriangle();
    Shader *shader = CreateShader();
    glm::mat4 projection = glm::perspective(45.0f, (GLfloat) window->GetHeight() / (GLfloat) window->GetHeight(), 0.1f,
                                            100.0f);
    Camera camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 0.01f, 1.0f);

    while (!window->ShouldClose()) {
        glfwPollEvents();
        camera.KeyControl(window->getKeys());

        if (direction) {
            tri_offset += tri_increment;
        } else {
            tri_offset -= tri_increment;
        }

        if (std::abs(tri_offset) >= tri_max_offset) {
            direction = !direction;
        }

        current_angle += angle_delta;
        if (current_angle >= 360.0f) {
            current_angle -= 360;
        }

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader->UseShader();

        glm::mat4 model(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.5f));
        model = glm::rotate(model, current_angle, glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.5, 0.5f, 0.5f));

        glUniformMatrix4fv(shader->GetModel(), 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(shader->GetProjection(), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(shader->GetView(), 1, GL_FALSE, glm::value_ptr(camera.CalculateViewMatrix()));

        for (auto mesh: meshes) {
            mesh->RenderMesh();
        }


        glUseProgram(0);
        window->SwapBuffers();
    }

    return 0;
}
