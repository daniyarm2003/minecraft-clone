#ifndef VBO_H
#define VBO_H

#include <glad/glad.h>

namespace GL {
    class VBO {
    public:
        VBO();
        ~VBO();

        void bind(GLenum target);
        void bufferData(const void* data, GLsizeiptr size, GLenum usage);
        void unbind();

        operator GLuint () const;

    private:
        GLuint id;
        GLenum target;

        VBO(const VBO&) = delete;
        VBO& operator=(const VBO&) = delete;
    };
}

#endif // VBO_H