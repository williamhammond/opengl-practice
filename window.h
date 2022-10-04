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

    bool *getKeys() { return keys; };

    // TODO: Add bool to see if the mouse moved since the last check to mak this more robust
    GLfloat getXDelta();
    GLfloat getYDelta();


private:
    GLFWwindow *main_window;

    GLint width, height;
    GLint buffer_width, buffer_height;

    bool keys[1024];

    GLfloat last_x;
    GLfloat last_y;
    GLfloat x_delta;
    GLfloat y_delta;
    bool is_first_movement;

    static void handleKeys(GLFWwindow *window, int key, int code, int action, int mode);

    static void handleMoues(GLFWwindow *window, double x_position, double y_position);

    void createCallbacks();
};


#endif //OPENGL_PRACTICE_WINDOW_H
