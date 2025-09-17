#include <glad/glad.h>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"

namespace GL {
    Shader::Shader(GLenum type, const char* source) {
        this->id = glCreateShader(type);
        glShaderSource(this->id, 1, &source, nullptr);
        glCompileShader(this->id);

        GLint success;
        glGetShaderiv(this->id, GL_COMPILE_STATUS, &success);
        if (!success) {
            char infoLog[512];
            glGetShaderInfoLog(this->id, 512, nullptr, infoLog);
            throw std::runtime_error(std::string("Shader compilation failed: ") + infoLog);
        }
    }

    Shader::~Shader() {
        glDeleteShader(this->id);
    }

    Shader::operator GLuint () const {
        return this->id;
    }

    Shader Shader::fromFile(GLenum type, const std::filesystem::path& path) {
        std::ifstream file(path, std::ios::in);

        if (!file.is_open()) {
            throw std::runtime_error("Failed to open shader file: " + path.string());
        }

        std::stringstream buffer;
        buffer << file.rdbuf();
        file.close();

        return Shader(type, buffer.str().c_str());
    }

    ShaderProgram::ShaderProgram() {
        this->id = glCreateProgram();
    }

    ShaderProgram::~ShaderProgram() {
        glDeleteProgram(this->id);
    }

    void ShaderProgram::attachShader(const Shader& shader) const {
        glAttachShader(this->id, shader);
    }

    void ShaderProgram::link() {
        glLinkProgram(this->id);

        GLint success;
        glGetProgramiv(this->id, GL_LINK_STATUS, &success);
        if (!success) {
            char infoLog[512];
            glGetProgramInfoLog(this->id, 512, nullptr, infoLog);
            throw std::runtime_error(std::string("Shader program linking failed: ") + infoLog);
        }
    }

    void ShaderProgram::use() const {
        glUseProgram(this->id);
    }

    GLint ShaderProgram::getUniformLocation(const char* name) const {
        return glGetUniformLocation(this->id, name);
    }

    void ShaderProgram::setBoolean(const char* name, GLboolean value) const {
        glUniform1i(this->getUniformLocation(name), static_cast<GLint>(value));
    }

    void ShaderProgram::setInteger(const char* name, GLint value) const {
        glUniform1i(this->getUniformLocation(name), value);
    }

    void ShaderProgram::setFloat(const char* name, GLfloat value) const {
        glUniform1f(this->getUniformLocation(name), value);
    }

    void ShaderProgram::setVec2(const char* name, const glm::vec2& value) const {
        glUniform2fv(this->getUniformLocation(name), 1, glm::value_ptr(value));
    }

    void ShaderProgram::setVec3(const char* name, const glm::vec3& value) const {
        glUniform3fv(this->getUniformLocation(name), 1, glm::value_ptr(value));
    }

    void ShaderProgram::setVec4(const char* name, const glm::vec4& value) const {
        glUniform4fv(this->getUniformLocation(name), 1, glm::value_ptr(value));
    }

    void ShaderProgram::setMat2(const char* name, const glm::mat2& mat) const {
        glUniformMatrix2fv(this->getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(mat));
    }

    void ShaderProgram::setMat3(const char* name, const glm::mat3& mat) const {
        glUniformMatrix3fv(this->getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(mat));
    }

    void ShaderProgram::setMat4(const char* name, const glm::mat4& mat) const {
        glUniformMatrix4fv(this->getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(mat));
    }

    void ShaderProgram::setTexture(const char* name, const Texture& texture, GLenum textureUnit) const {
        glUniform1i(this->getUniformLocation(name), textureUnit - GL_TEXTURE0);
    }

    void ShaderProgram::bindAndSetTexture(const char* name, const Texture& texture, GLenum textureUnit) {
        texture.bind(textureUnit);
        this->setTexture(name, texture, textureUnit);
    }
}