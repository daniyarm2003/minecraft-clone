#include <glad/glad.h>
#include "vao.h"

namespace GL {
    VAO::VAO() {
        glGenVertexArrays(1, &this->id);
    }

    VAO::~VAO() {
        glDeleteVertexArrays(1, &this->id);
    }

    void VAO::bind() {
        glBindVertexArray(this->id);
    }

    void VAO::unbind() {
        glBindVertexArray(0);
    }

    void VAO::setVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* offset) {
        glVertexAttribPointer(index, size, type, normalized, stride, offset);
        glEnableVertexAttribArray(index);
    }

    void VAO::setVertexIntAttribPointer(GLuint index, GLint size, GLenum type, GLsizei stride, const void* offset) {
        glVertexAttribIPointer(index, size, type, stride, offset);
        glEnableVertexAttribArray(index);
    }

    VAO::operator GLuint() const {
        return this->id;
    }
}