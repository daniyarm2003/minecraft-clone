#include "block_atlas.h"

#include "chunk.h"

namespace World::Chunks {
    BlockAtlas::BlockAtlas(int widthInBlocks, int heightInBlocks, int blockPixelSize)
        : texture(GL_TEXTURE_2D), width(widthInBlocks), height(heightInBlocks), blockPixelSize(blockPixelSize) {}

    int BlockAtlas::getWidthInBlocks() const {
        return this->width;
    }

    int BlockAtlas::getHeightInBlocks() const {
        return this->height;
    }

    int BlockAtlas::getBlockPixelSize() const {
        return this->blockPixelSize;
    }

    void BlockAtlas::loadTextureDataFromFile(const std::filesystem::path& path) {
        this->texture.bind();
        this->texture.loadImage2DFromFile(path);

        this->texture.setMinFilter(GL_NEAREST);
        this->texture.setMagFilter(GL_NEAREST);

        this->texture.setWrapS(GL_REPEAT);
        this->texture.setWrapT(GL_REPEAT);

        this->texture.unbind();
    }

    void BlockAtlas::setUniforms(GL::ShaderProgram& shaderProgram) const {
        shaderProgram.setInteger("blockAtlasWidthInBlocks", this->width);
        shaderProgram.setInteger("blockAtlasHeightInBlocks", this->height);
        shaderProgram.setInteger("blockAtlasBlockPixelSize", this->blockPixelSize);
        shaderProgram.setInteger("blockSize", Chunk::BLOCK_SIZE);
    }

    void BlockAtlas::bindTexture() const {
        this->texture.bind();
    }

    void BlockAtlas::unbindTexture() const {
        this->texture.unbind();
    }

    void BlockAtlas::bindAndSetTexture(GL::ShaderProgram& shaderProgram) const {
        shaderProgram.bindAndSetTexture("blockAtlas", this->texture);
    }
}