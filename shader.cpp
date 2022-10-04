#include "shader.h"

#include <cstring>
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

Shader::Shader() {
    shader_id = 0;
    uniform_projection = 0;
    uniform_model = 0;
    uniform_view = 0;
}

Shader::~Shader() {
    ClearShader();
}

void Shader::Compile() {
    GLint result;
    GLchar error_log[1024];

    glLinkProgram(shader_id);
    glGetProgramiv(shader_id, GL_LINK_STATUS, &result);
    if (!result) {
        glGetProgramInfoLog(shader_id, sizeof(error_log), nullptr, error_log);
        printf("Error linking program: %s \n", error_log);
    }

    glValidateProgram(shader_id);
    glGetProgramiv(shader_id, GL_VALIDATE_STATUS, &result);
    if (!result) {
        glGetProgramInfoLog(shader_id, sizeof(error_log), nullptr, error_log);
        printf("Error validating program: %s \n", error_log);
    }

    uniform_model = glGetUniformLocation(shader_id, "model");
    uniform_projection = glGetUniformLocation(shader_id, "projection");
    uniform_view = glGetUniformLocation(shader_id, "view");
}

void Shader::CreateFromFile(const char *vertex_shader_path, const char *fragment_shader_path) {
    shader_id = glCreateProgram();
    if (!shader_id) {
        printf("Error creating shader_id program");
        return;
    }

    std::string vertex_program = readFile(vertex_shader_path);
    AddShader(vertex_program.c_str(), GL_VERTEX_SHADER);

    std::string fragment_program = readFile(fragment_shader_path);
    AddShader(fragment_program.c_str(), GL_FRAGMENT_SHADER);

    Compile();
}

void Shader::UseShader() {
    glUseProgram(shader_id);
}

void Shader::ClearShader() {
    if (shader_id != 0) {
        glDeleteProgram(shader_id);
        shader_id = 0;
    }
    uniform_projection = 0;
    uniform_model = 0;
}

GLuint Shader::GetModel() {
    return uniform_model;
}

GLuint Shader::GetProjection() {
    return uniform_projection;
}

GLuint Shader::GetView() {
    return uniform_view;
}

std::string Shader::readFile(const char *filePath) {
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

void Shader::AddShader(const char *shaderCode, GLenum shaderType) {
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

    glAttachShader(shader_id, shader);
}
