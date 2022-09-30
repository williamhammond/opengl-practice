#include <cstdio>
#include "window.h"
#include "cmake-build-debug-visual-studio/_deps/glfw-src/include/GLFW/glfw3.h"

Window::Window(GLint window_width, GLint window_height) {
    width = window_width;
    height = window_height;
}

Window::~Window() {
    glfwDestroyWindow(main_window);
    glfwTerminate();
}

int Window::Initalize() {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    if (!glfwInit()) {
        printf("GLFW initialization failed!");
        glfwTerminate();
        return 1;
    }

    main_window = glfwCreateWindow(width, height, "Test Window", nullptr, nullptr);
    if (!main_window) {
        printf("GLFW window creation failed!");
        glfwTerminate();
        return -1;
    }


    glfwGetFramebufferSize(main_window, &width, &height);
    glfwMakeContextCurrent(main_window);

    glewExperimental = GL_TRUE;
    GLenum error = glewInit();
    if (error != GLEW_OK) {
        printf("Error: %s", glewGetErrorString(error));
        glfwDestroyWindow(main_window);
        glfwTerminate();
        return 1;
    }

    glEnable(GL_DEPTH_TEST);

    glViewport(0, 0, width, height);
    return 0;
}
