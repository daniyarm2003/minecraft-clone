#include "texture.h"

#include <fstream>
#include <stb_image.h>

namespace GL {
    Texture::Texture(GLenum target) : target(target) {
        glGenTextures(1, &this->id);
    }

    Texture::~Texture() {
        glDeleteTextures(1, &this->id);
    }

    void Texture::bind(GLenum textureUnit) const {
        glActiveTexture(textureUnit);
        glBindTexture(this->target, this->id);
    }

    void Texture::unbind() const {
        glBindTexture(this->target, 0);
    }

    void Texture::setParameter(GLenum pname, GLint param) {
        glTexParameteri(this->target, pname, param);
    }

    void Texture::setMinFilter(GLenum filter) {
        this->setParameter(GL_TEXTURE_MIN_FILTER, filter);
    }

    void Texture::setMagFilter(GLenum filter) {
        this->setParameter(GL_TEXTURE_MAG_FILTER, filter);
    }

    void Texture::setWrapS(GLenum mode) {
        this->setParameter(GL_TEXTURE_WRAP_S, mode);
    }

    void Texture::setWrapT(GLenum mode) {
        this->setParameter(GL_TEXTURE_WRAP_T, mode);
    }

    void Texture::setWrapR(GLenum mode) {
        this->setParameter(GL_TEXTURE_WRAP_R, mode);
    }

    void Texture::loadImage2DFromFile(const std::filesystem::path& path, bool flipVertically) {
        if (flipVertically) {
            stbi_set_flip_vertically_on_load(true);
        }

        int width, height, channels;
        unsigned char* data = stbi_load(path.string().c_str(), &width, &height, &channels, 0);
        if (!data) {
            throw std::runtime_error("Failed to load texture image");
        }

        GLenum format = (channels == 4) ? GL_RGBA : (channels == 3) ? GL_RGB : (channels == 1) ? GL_RED : 0;
        if (format == 0) {
            stbi_image_free(data);
            throw std::runtime_error("Unsupported number of channels in texture image");
        }

        this->setImage2D(0, format, width, height, format, GL_UNSIGNED_BYTE, data);
        stbi_image_free(data);
    }

    void Texture::setImage2D(GLint level, GLenum internalFormat, GLsizei width, GLsizei height, GLenum format, GLenum type, const void* data) {
        glTexImage2D(this->target, level, internalFormat, width, height, 0, format, type, data);
    }

    void Texture::generateMipmap() {
        glGenerateMipmap(this->target);
    }

    Texture::operator GLuint() const {
        return this->id;
    }
}