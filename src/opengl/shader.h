#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <filesystem>

#include "texture.h"

namespace GL {
    class Shader {
    public:
        Shader(GLenum type, const char* source);
        ~Shader();

        operator GLuint () const;

        static Shader fromFile(GLenum type, const std::filesystem::path& path);

    private:
        GLuint id;

        Shader(const Shader&) = delete;
        Shader& operator=(const Shader&) = delete;
    };

    class ShaderProgram {
    public:
        ShaderProgram();
        ~ShaderProgram();

        void attachShader(const Shader& shader) const;
        void link();
        void use() const;

        operator GLuint () const;

        GLint getUniformLocation(const char* name) const;

        void setBoolean(const char* name, GLboolean value) const;
        void setInteger(const char* name, GLint value) const;
        void setFloat(const char* name, GLfloat value) const;

        void setVec2(const char* name, const glm::vec2& value) const;
        void setVec3(const char* name, const glm::vec3& value) const;
        void setVec4(const char* name, const glm::vec4& value) const;

        void setMat2(const char* name, const glm::mat2& mat) const;
        void setMat3(const char* name, const glm::mat3& mat) const;
        void setMat4(const char* name, const glm::mat4& mat) const;

        void bindAndSetTexture(const char* name, const Texture& texture, GLenum textureUnit = GL_TEXTURE0);
        void setTexture(const char* name, const Texture& texture, GLenum textureUnit = GL_TEXTURE0) const;

    private:
        GLuint id;

        ShaderProgram(const ShaderProgram&) = delete;
        ShaderProgram& operator=(const ShaderProgram&) = delete;
    };
}

#endif // SHADER_H