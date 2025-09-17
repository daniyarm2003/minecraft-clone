#ifndef BLOCK_ATLAS_H
#define BLOCK_ATLAS_H

#include <cstdint>
#include <glm/glm.hpp>

#include "../../opengl/texture.h"
#include "../../opengl/shader.h"

namespace World::Chunks {
    class BlockAtlas {
    public:
        BlockAtlas(int widthInBlocks, int heightInBlocks, int blockPixelSize);

        int getWidthInBlocks() const;
        int getHeightInBlocks() const;
        int getBlockPixelSize() const;

        void loadTextureDataFromFile(const std::filesystem::path& path);

        void setUniforms(GL::ShaderProgram& shaderProgram) const;

        void bindTexture() const;
        void unbindTexture() const;

        void bindAndSetTexture(GL::ShaderProgram& shaderProgram) const;

    private:
        GL::Texture texture;

        int width;
        int height;
        int blockPixelSize;
    };
}

#endif // BLOCK_ATLAS_H