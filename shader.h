#ifndef OPENGL_PRACTICE_SHADER_H
#define OPENGL_PRACTICE_SHADER_H

#include<string>
#include <GL/glew.h>


class Shader {
public:
    Shader();

    ~Shader();

    void CreateFromFile(const char *vertex_shader_path, const char *fragment_shader_path);


    void UseShader();
    void ClearShader();


    GLuint GetModel();
    GLuint GetProjection();
    GLuint GetView();


private:
    void AddShader(const char *shaderCode, GLenum shaderType);
    void Compile();
    std::string readFile(const char *filePath);
    GLuint shader_id, uniform_model, uniform_projection, uniform_view;
};
#endif //OPENGL_PRACTICE_SHADER_H
