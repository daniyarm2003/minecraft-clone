#ifndef VAO_H
#define VAO_H

#include <glad/glad.h>

namespace GL {
    class VAO {
    public:
        VAO();
        ~VAO();

        void bind();
        void unbind();

        void setVertexIntAttribPointer(GLuint index, GLint size, GLenum type, GLsizei stride, const void* offset);
        void setVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* offset);

        operator GLuint () const;

    private:
        GLuint id;

        VAO(const VAO&) = delete;
        VAO& operator=(const VAO&) = delete;
    };
}

#endif // VAO_H