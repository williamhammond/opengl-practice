#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>

#include <filesystem>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "mesh.h"
#include "shader.h"

// Window dimensions
const GLint WIDTH = 800;
const GLint HEIGHT = 600;

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
    if (!glfwInit()) {
        printf("GLFW initialization failed!");
        glfwTerminate();
        return 1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    auto *mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "Test Window", nullptr, nullptr);
    if (!mainWindow) {
        printf("GLFW window creation failed!");
        glfwTerminate();
        return 1;
    }

    int bufferWidth;
    int bufferHeight;
    glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);
    glfwMakeContextCurrent(mainWindow);

    glewExperimental = GL_TRUE;
    GLenum error = glewInit();
    if (error != GLEW_OK) {
        printf("Error: %s", glewGetErrorString(error));
        glfwDestroyWindow(mainWindow);
        glfwTerminate();
        return 1;
    }

    glEnable(GL_DEPTH_TEST);

    glViewport(0, 0, bufferWidth, bufferHeight);
    CreateTriangle();

    Shader *shader = CreateShader();
    glm::mat4 projection = glm::perspective(45.0f, (GLfloat) WIDTH / (GLfloat) HEIGHT, 0.1f, 100.0f);

    while (!glfwWindowShouldClose(mainWindow)) {
        glfwPollEvents();
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

        for (auto mesh: meshes) {
            mesh->RenderMesh();
        }


        glUseProgram(0);
        glfwSwapBuffers(mainWindow);
    }

    return 0;
}
