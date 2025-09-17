#include <glad/glad.h>
#include "vbo.h"

namespace GL {
    VBO::VBO() {
        glGenBuffers(1, &this->id);
    }

    VBO::~VBO() {
        glDeleteBuffers(1, &this->id);
    }

    void VBO::bind(GLenum target) {
        this->target = target;
        glBindBuffer(target, this->id);
    }

    void VBO::bufferData(const void* data, GLsizeiptr size, GLenum usage) {
        glBufferData(this->target, size, data, usage);
    }

    void VBO::unbind() {
        glBindBuffer(this->target, 0);
    }

    VBO::operator GLuint() const {
        return this->id;
    }
}