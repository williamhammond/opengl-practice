#ifndef OPENGL_PRACTICE_MESH_H
#define OPENGL_PRACTICE_MESH_H


#include <GL/glew.h>

class Mesh {
public:
    Mesh();

    ~Mesh();

    void CreateMesh(GLfloat *vertices, unsigned int *indices, unsigned int vertex_count, unsigned int index_count);

    void RenderMesh();

    void ClearMesh();

private:
    GLuint VAO, VBO, IBO;
    GLsizei size;
};


#endif //OPENGL_PRACTICE_MESH_H
