#ifndef OPENGL_PRACTICE_WINDOW_H
#define OPENGL_PRACTICE_WINDOW_H


#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window {
public:
    Window(GLint window_width, GLint window_height);

    ~Window();

    int Initalize();

    GLint GetWidth() { return width; };

    GLint GetHeight() { return height; };

    bool ShouldClose() { return glfwWindowShouldClose(main_window); };

    void SwapBuffers() { glfwSwapBuffers(main_window); };

private:
    GLFWwindow* main_window;
    GLint width, height;

};


#endif //OPENGL_PRACTICE_WINDOW_H
