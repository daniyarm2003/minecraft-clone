#include "chunk.h"

#include "blocks.h"
#include "chunk_manager.h"

#include <iostream>

namespace World::Chunks {
    Chunk::Chunk(ChunkManager* chunkManager, int chunkCoordX, int chunkCoordZ) : chunkCoordX(chunkCoordX), chunkCoordZ(chunkCoordZ), chunkManager(chunkManager) {
        for(size_t i = 0; i < this->blocks.size(); i++) {
            this->blocks[i] = Blocks::AIR;
        }
    }

    void Chunk::render(GL::GLFWContext& context, GL::ShaderProgram& shader, const BlockAtlas& blockAtlas) {
        shader.setInteger("chunkCoordX", this->getChunkCoordX());
        shader.setInteger("chunkCoordZ", this->getChunkCoordZ());

        this->mesh.render(this, blockAtlas, context, this->chunkManager);
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

    void Chunk::setBlock(const glm::ivec3& blockPos, const Block& block, bool naturalGeneration) {
        this->setBlock(blockPos.x, blockPos.y, blockPos.z, block, naturalGeneration);
    }

    void Chunk::setBlock(int x, int y, int z, const Block& block, bool naturalGeneration) {
        if (x < 0 || x >= CHUNK_SIZE_X || y < 0 || y >= CHUNK_SIZE_Y || z < 0 || z >= CHUNK_SIZE_Z) {
            return;
        }

        int blockIndex = x + y * CHUNK_SIZE_X + z * CHUNK_SIZE_X * CHUNK_SIZE_Y;

        this->blocks[blockIndex] = block;

        if(!naturalGeneration) {
            this->modifiedBlockCoords.insert(blockIndex);
        }

        this->mesh.markDirty();

        if(x == 0 && this->chunkManager->isChunkLoaded(this->chunkCoordX - 1, this->chunkCoordZ)) {
            this->chunkManager->getChunk(this->chunkCoordX - 1, this->chunkCoordZ).lock()->meshMarkDirty();
        }
        else if(x == CHUNK_SIZE_X - 1 && this->chunkManager->isChunkLoaded(this->chunkCoordX + 1, this->chunkCoordZ)) {
            this->chunkManager->getChunk(this->chunkCoordX + 1, this->chunkCoordZ).lock()->meshMarkDirty();
        }

        if(z == 0 && this->chunkManager->isChunkLoaded(this->chunkCoordX, this->chunkCoordZ - 1)) {
            this->chunkManager->getChunk(this->chunkCoordX, this->chunkCoordZ - 1).lock()->meshMarkDirty();
        }
        else if(z == CHUNK_SIZE_Z - 1 && this->chunkManager->isChunkLoaded(this->chunkCoordX, this->chunkCoordZ + 1)) {
            this->chunkManager->getChunk(this->chunkCoordX, this->chunkCoordZ + 1).lock()->meshMarkDirty();
        }
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

    std::vector<ChunkModification> Chunk::getChunkModifications() const {
        std::vector<ChunkModification> chunkMods(this->modifiedBlockCoords.size());

        for(const int& modifiedBlockCoord : this->modifiedBlockCoords) {
            int xCoord = modifiedBlockCoord % CHUNK_SIZE_X;
            int yCoord = (modifiedBlockCoord % (CHUNK_SIZE_X * CHUNK_SIZE_Y)) / CHUNK_SIZE_X;
            int zCoord = modifiedBlockCoord / (CHUNK_SIZE_X * CHUNK_SIZE_Y);

            glm::ivec3 blockPos = { xCoord, yCoord, zCoord };
            const Block block = this->getBlock(blockPos);

            chunkMods.push_back({ blockPos, block });
        }

        return chunkMods;
    }
}