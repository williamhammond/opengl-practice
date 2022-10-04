#include <cstdio>
#include "window.h"
#include "cmake-build-debug-visual-studio/_deps/glfw-src/include/GLFW/glfw3.h"

Window::Window(GLint window_width, GLint window_height) {
    width = window_width;
    height = window_height;

    for (bool &key: keys) {
        key = false;
    }
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
    createCallbacks();
    glfwSetInputMode(main_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

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

    glfwSetWindowUserPointer(main_window, this);
    return 0;
}

void Window::createCallbacks() {
    glfwSetKeyCallback(main_window, handleKeys);
    glfwSetCursorPosCallback(main_window, handleMoues);
}

void Window::handleKeys(GLFWwindow *window, int key, int code, int action, int mode) {
    auto *my_window = static_cast<Window *>(glfwGetWindowUserPointer(window));

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

    if (key >= 0 && key < 1024) {
        if (action == GLFW_PRESS) {
            my_window->keys[key] = true;
        } else if (action == GLFW_RELEASE) {
            my_window->keys[key] = false;
        }
    }
}

void Window::handleMoues(GLFWwindow *window, double x_position, double y_position) {
    auto *my_window = static_cast<Window *>(glfwGetWindowUserPointer(window));
    if (my_window->is_first_movement) {
        my_window->last_x = x_position;
        my_window->last_y = y_position;
        my_window->is_first_movement = false;
    }

    my_window->x_delta = x_position - my_window->last_x;
    my_window->y_delta = my_window->last_y - y_position;

    my_window->last_x = x_position;
    my_window->last_y = y_position;
}

GLfloat Window::getXDelta() {
    GLfloat delta = x_delta;
    x_delta = 0;
    return delta;
}

GLfloat Window::getYDelta() {
    GLfloat delta = y_delta;
    y_delta = 0;
    return delta;
}

