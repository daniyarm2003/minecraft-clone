#include "chunk.h"

#include "blocks.h"
#include "chunk_manager.h"

namespace World::Chunks {
    Chunk::Chunk(int chunkCoordX, int chunkCoordZ) : chunkCoordX(chunkCoordX), chunkCoordZ(chunkCoordZ) {
        for(size_t i = 0; i < this->blocks.size(); i++) {
            this->blocks[i] = Blocks::AIR;
            this->solidFlags[i] = false;
        }
    }

    void Chunk::render(GL::GLFWContext& context, GL::ShaderProgram& shader, const BlockAtlas& blockAtlas, ChunkManager* chunkManager) {
        shader.setInteger("chunkCoordX", this->getChunkCoordX());
        shader.setInteger("chunkCoordZ", this->getChunkCoordZ());

        this->mesh.render(this, blockAtlas, context, chunkManager);
    }

    const Block& Chunk::getBlock(const glm::ivec3& blockPos) const {
        return this->getBlock(blockPos.x, blockPos.y, blockPos.z);
    }

    const Block& Chunk::getBlock(int x, int y, int z) const {
        if (x < 0 || x >= CHUNK_SIZE_X || y < 0 || y >= CHUNK_SIZE_Y || z < 0 || z >= CHUNK_SIZE_Z) {
            return Blocks::AIR;
        }

        return this->blocks[x + y * CHUNK_SIZE_X + z * CHUNK_SIZE_X * CHUNK_SIZE_Y];
    }

    void Chunk::setBlock(const glm::ivec3& blockPos, const Block& block) {
        this->setBlock(blockPos.x, blockPos.y, blockPos.z, block);
    }

    void Chunk::setBlock(int x, int y, int z, const Block& block) {
        if (x < 0 || x >= CHUNK_SIZE_X || y < 0 || y >= CHUNK_SIZE_Y || z < 0 || z >= CHUNK_SIZE_Z) {
            return;
        }

        int blockIndex = x + y * CHUNK_SIZE_X + z * CHUNK_SIZE_X * CHUNK_SIZE_Y;

        this->blocks[blockIndex] = block;
        this->solidFlags[blockIndex] = block.isSolid();

        this->mesh.markDirty();
    }

    bool Chunk::isBlockSolid(const glm::ivec3& blockPos) const {
        return this->isBlockSolid(blockPos.x, blockPos.y, blockPos.z);
    }

    bool Chunk::isBlockSolid(int x, int y, int z) const {
        if (x < 0 || x >= CHUNK_SIZE_X || y < 0 || y >= CHUNK_SIZE_Y || z < 0 || z >= CHUNK_SIZE_Z) {
            return false;
        }

        return this->solidFlags[x + y * CHUNK_SIZE_X + z * CHUNK_SIZE_X * CHUNK_SIZE_Y];
    }

    int Chunk::getChunkCoordX() const {
        return this->chunkCoordX;
    }

    int Chunk::getChunkCoordZ() const {
        return this->chunkCoordZ;
    }

    void Chunk::meshMarkDirty() {
        this->mesh.markDirty();
    }
}