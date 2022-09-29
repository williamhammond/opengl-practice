#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <glm/vec3.hpp> // glm::vec3

#include <filesystem>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

// Window dimensions
const GLint WIDTH = 800;
const GLint HEIGHT = 600;

GLuint VAO, VBO, root_shader;


std::string readFile(const char *filePath) {
    std::ifstream fileStream(filePath, std::ios::in);

    if (!fileStream.is_open()) {
        std::cerr << "Could not read file " << filePath << ". File does not exist." << std::endl;
        return "";
    }

    std::string content{};
    std::string line{};
    while (!fileStream.eof()) {
        std::getline(fileStream, line);
        content.append(line + "\n");
    }

    fileStream.close();
    return content;
}

void CreateTriangle() {
    GLfloat vertices[] = {
            -1.0f, -1.0f, 0.0f,
            1.0f, -1.0f, 0.0f,
            0.0f, 1.0f, 0.0f
    };

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

void AddShader(GLuint program, const char *shaderCode, GLenum shaderType) {
    GLuint shader = glCreateShader(shaderType);

    const GLchar *code[1];
    code[0] = shaderCode;

    GLint code_length[1];
    code_length[0] = strlen(shaderCode);

    glShaderSource(shader, 1, code, code_length);
    glCompileShader(shader);

    GLint result;
    GLchar error_log[1024];

    glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
    if (!result) {
        glGetShaderInfoLog(shader, sizeof(error_log), nullptr, error_log);
        printf("Error compiling the %d shader: %s \n", shaderType, error_log);
    }

    glAttachShader(program, shader);
}
void CompileShaders() {
    root_shader = glCreateProgram();
    if (!root_shader) {
        printf("Error creating root_shader program");
        return;
    }

    std::cout << std::filesystem::current_path() << std::endl;

    std::string vertex_program = readFile("../vertex.glsl");
    AddShader(root_shader, vertex_program.c_str(), GL_VERTEX_SHADER);

    std::string fragment_program = readFile("../fragment.glsl");
    AddShader(root_shader, fragment_program.c_str(), GL_FRAGMENT_SHADER);

    GLint result;
    GLchar error_log[1024];

    glLinkProgram(root_shader);
    glGetProgramiv(root_shader, GL_LINK_STATUS, &result);
    if (!result) {
        glGetProgramInfoLog(root_shader, sizeof(error_log), nullptr, error_log);
        printf("Error linking program: %s \n", error_log);
    }

    glValidateProgram(root_shader);
    glGetProgramiv(root_shader, GL_VALIDATE_STATUS, &result);
    if (!result) {
        glGetProgramInfoLog(root_shader, sizeof(error_log), nullptr, error_log);
        printf("Error validating program: %s \n", error_log);
    }
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
    if (glewInit() != GLEW_OK) {
        printf("Glew initialization failed");
        glfwDestroyWindow(mainWindow);
        glfwTerminate();
        return 1;
    }

    glViewport(0, 0, bufferWidth, bufferHeight);
    CreateTriangle();
    CompileShaders();

    while (!glfwWindowShouldClose(mainWindow)) {
        glfwPollEvents();

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(root_shader);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);
        glUseProgram(0);

        glfwSwapBuffers(mainWindow);
    }

    return 0;
}
