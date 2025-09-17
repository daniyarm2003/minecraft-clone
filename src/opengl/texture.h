#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>
#include <filesystem>

namespace GL {
    class Texture {
    public:

    Texture(GLenum target);
    ~Texture();

    void bind(GLenum textureUnit = GL_TEXTURE0) const;
    void unbind() const;

    void setParameter(GLenum pname, GLint param);

    void setMinFilter(GLenum filter);
    void setMagFilter(GLenum filter);

    void setWrapS(GLenum mode);
    void setWrapT(GLenum mode);
    void setWrapR(GLenum mode);

    void loadImage2DFromFile(const std::filesystem::path& path, bool flipVertically = true);
    void setImage2D(GLint level, GLenum internalFormat, GLsizei width, GLsizei height, GLenum format, GLenum type, const void* data);
    void generateMipmap();

    operator GLuint () const;

    private:
        GLuint id;
        GLenum target;

        Texture(const Texture&) = delete;
        Texture& operator=(const Texture&) = delete;
    };  
}

#endif // TEXTURE_H