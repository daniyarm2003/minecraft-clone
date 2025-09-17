#include "chunk_manager.h"

#include <iostream>
#include <glm/gtc/constants.hpp>
#include <stb_perlin.h>

#include "blocks.h"

namespace World::Chunks {
    int ChunkManager::getRenderDistance() const {
        return this->curRenderDistance;
    }

    void ChunkManager::setRenderDistance(int renderDistance) {
        if(this->curRenderDistance == renderDistance) {
            return;
        }

        auto curLoadedChunks = std::move(this->loadedChunks);

        int lengthInChunks = 2 * renderDistance + 1;

        this->loadedChunks.clear();
        this->loadedChunks.resize(lengthInChunks * lengthInChunks);

        for(int offX = -renderDistance; offX <= renderDistance; offX++) {
            for(int offZ = -renderDistance; offZ <= renderDistance; offZ++) {
                int newChunkIndex = this->getChunkVectorIndex(offX, offZ, renderDistance);
                int distFromCenter = this->curRenderDistance - 1;
                
                if(offX < -distFromCenter || offX > distFromCenter || offZ < -distFromCenter || offZ > distFromCenter) {
                    this->loadedChunks[newChunkIndex] = this->createAndPopulateChunk(this->centerChunkX + offX, this->centerChunkZ + offZ);
                }
                else {
                    int curChunkIndex = this->getChunkVectorIndex(offX, offZ, this->curRenderDistance);
                    this->loadedChunks[newChunkIndex] = curLoadedChunks[curChunkIndex];
                }
            }
        }

        this->curRenderDistance = renderDistance;
    }

    void ChunkManager::loadChunks(const glm::vec3& pos) {
        int chunkX = (int)glm::round(pos.x / (Chunk::BLOCK_SIZE_FLOAT * (float)Chunk::CHUNK_SIZE_X));
        int chunkZ = (int)glm::round(pos.z / (Chunk::BLOCK_SIZE_FLOAT * (float)Chunk::CHUNK_SIZE_Z));

        this->loadChunks(chunkX, chunkZ);
    }

    void ChunkManager::loadChunks(int chunkX, int chunkZ) {
        int deltaX = chunkX - this->centerChunkX;
        int deltaZ = chunkZ - this->centerChunkZ;

        if(deltaX > 0) {
            for(int xOff = -this->curRenderDistance; xOff <= this->curRenderDistance; xOff++) {
                for(int zOff = -this->curRenderDistance; zOff <= this->curRenderDistance; zOff++) {
                    int curChunkIndex = this->getChunkVectorIndex(xOff, zOff, this->curRenderDistance);
                    int offsetChunkIndex = this->getChunkVectorIndex(xOff + deltaX, zOff, this->curRenderDistance);

                    if(xOff <= this->curRenderDistance - deltaX) {
                        this->loadedChunks[curChunkIndex] = this->loadedChunks[offsetChunkIndex];

                        if(xOff == this->curRenderDistance - deltaX) {
                            this->loadedChunks[curChunkIndex]->meshMarkDirty();
                        }
                    }
                    else {
                        this->loadedChunks[curChunkIndex] = this->createAndPopulateChunk(this->centerChunkX + xOff + deltaX, this->centerChunkZ + zOff);
                    }
                }
            }
        }
        else if(deltaX < 0) {
            for(int xOff = this->curRenderDistance; xOff >= -this->curRenderDistance; xOff--) {
                for(int zOff = -this->curRenderDistance; zOff <= this->curRenderDistance; zOff++) {
                    int curChunkIndex = this->getChunkVectorIndex(xOff, zOff, this->curRenderDistance);
                    int offsetChunkIndex = this->getChunkVectorIndex(xOff + deltaX, zOff, this->curRenderDistance);

                    if(xOff >= -this->curRenderDistance - deltaX) {
                        this->loadedChunks[curChunkIndex] = this->loadedChunks[offsetChunkIndex];

                        if(xOff == -this->curRenderDistance - deltaX) {
                            this->loadedChunks[curChunkIndex]->meshMarkDirty();
                        }
                    }
                    else {
                        this->loadedChunks[curChunkIndex] = this->createAndPopulateChunk(this->centerChunkX + xOff + deltaX, this->centerChunkZ + zOff);
                    }
                }
            }
        }

        if(deltaZ > 0) {
            for(int zOff = -this->curRenderDistance; zOff <= this->curRenderDistance; zOff++) {
                for(int xOff = -this->curRenderDistance; xOff <= this->curRenderDistance; xOff++) {
                    int curChunkIndex = this->getChunkVectorIndex(xOff, zOff, this->curRenderDistance);
                    int offsetChunkIndex = this->getChunkVectorIndex(xOff, zOff + deltaZ, this->curRenderDistance);

                    if(zOff <= this->curRenderDistance - deltaZ) {
                        this->loadedChunks[curChunkIndex] = this->loadedChunks[offsetChunkIndex];

                        if(zOff == this->curRenderDistance - deltaZ) {
                            this->loadedChunks[curChunkIndex]->meshMarkDirty();
                        }
                    }
                    else {
                        this->loadedChunks[curChunkIndex] = this->createAndPopulateChunk(this->centerChunkX + xOff, this->centerChunkZ + zOff + deltaZ);
                    }
                }
            }
        }
        else if(deltaZ < 0) {
            for(int zOff = this->curRenderDistance; zOff >= -this->curRenderDistance; zOff--) {
                for(int xOff = -this->curRenderDistance; xOff <= this->curRenderDistance; xOff++) {
                    int curChunkIndex = this->getChunkVectorIndex(xOff, zOff, this->curRenderDistance);
                    int offsetChunkIndex = this->getChunkVectorIndex(xOff, zOff + deltaZ, this->curRenderDistance);

                    if(zOff >= -this->curRenderDistance - deltaZ) {
                        this->loadedChunks[curChunkIndex] = this->loadedChunks[offsetChunkIndex];

                        if(zOff == -this->curRenderDistance - deltaZ) {
                            this->loadedChunks[curChunkIndex]->meshMarkDirty();
                        }
                    }
                    else {
                        this->loadedChunks[curChunkIndex] = this->createAndPopulateChunk(this->centerChunkX + xOff, this->centerChunkZ + zOff + deltaZ);
                    }
                }
            }
        }

        this->centerChunkX = chunkX;
        this->centerChunkZ = chunkZ;
    }

    bool ChunkManager::isChunkLoaded(int chunkX, int chunkZ) const {
        int deltaX = chunkX - this->centerChunkX;
        int deltaZ = chunkZ - this->centerChunkZ;

        return deltaX >= -this->curRenderDistance && deltaX <= this->curRenderDistance && deltaZ >= -this->curRenderDistance && deltaZ <= this->curRenderDistance;
    }

    std::weak_ptr<Chunk> ChunkManager::getChunk(int chunkX, int chunkZ) {
        if(!this->isChunkLoaded(chunkX, chunkZ)) {
            return std::weak_ptr<Chunk>();
        }

        int deltaX = chunkX - this->centerChunkX;
        int deltaZ = chunkZ - this->centerChunkZ;

        int chunkIndex = this->getChunkVectorIndex(deltaX, deltaZ, this->curRenderDistance);

        return std::weak_ptr<Chunk>(this->loadedChunks[chunkIndex]);
    }

    bool ChunkManager::isBlockPosLoaded(const glm::ivec3& blockPos) const {
        return this->isBlockPosLoaded(blockPos.x, blockPos.y, blockPos.z);
    }

    bool ChunkManager::isBlockPosLoaded(int x, int y, int z) const {
        bool negativeChunkOffsetX = x < 0 && x % Chunk::CHUNK_SIZE_X != 0;
        bool negativeChunkOffsetZ = z < 0 && z % Chunk::CHUNK_SIZE_Z != 0;

        int chunkX = x / Chunk::CHUNK_SIZE_X - (negativeChunkOffsetX ? 1 : 0);
        int chunkZ = z / Chunk::CHUNK_SIZE_Z - (negativeChunkOffsetZ ? 1 : 0);

        return this->isChunkLoaded(chunkX, chunkZ) && y >= 0 && y < Chunk::CHUNK_SIZE_Y;
    }

    const Block& ChunkManager::getBlock(const glm::ivec3& blockPos) const {
        return this->getBlock(blockPos.x, blockPos.y, blockPos.z);
    }

    const Block& ChunkManager::getBlock(int x, int y, int z) const {
        if(!this->isBlockPosLoaded(x, y, z)) {
            return Blocks::AIR;
        }

        bool negativeChunkOffsetX = x < 0 && x % Chunk::CHUNK_SIZE_X != 0;
        bool negativeChunkOffsetZ = z < 0 && z % Chunk::CHUNK_SIZE_Z != 0;

        int chunkX = x / Chunk::CHUNK_SIZE_X - (negativeChunkOffsetX ? 1 : 0);
        int chunkZ = z / Chunk::CHUNK_SIZE_Z - (negativeChunkOffsetZ ? 1 : 0);

        int blockX = x - Chunk::CHUNK_SIZE_X * chunkX;
        int blockZ = z - Chunk::CHUNK_SIZE_Z * chunkZ;

        int deltaX = chunkX - this->centerChunkX;
        int deltaZ = chunkZ - this->centerChunkZ;

        int chunkIndex = this->getChunkVectorIndex(deltaX, deltaZ, this->curRenderDistance);

        return this->loadedChunks[chunkIndex]->getBlock(blockX, y, blockZ);
    }

    void ChunkManager::setBlock(const glm::ivec3& blockPos, const Block& block) {
        this->setBlock(blockPos.x, blockPos.y, blockPos.z, block);
    }

    void ChunkManager::setBlock(int x, int y, int z, const Block& block) {
        if(!this->isBlockPosLoaded(x, y, z)) {
            return;
        }

        bool negativeChunkOffsetX = x < 0 && x % Chunk::CHUNK_SIZE_X != 0;
        bool negativeChunkOffsetZ = z < 0 && z % Chunk::CHUNK_SIZE_Z != 0;

        int chunkX = x / Chunk::CHUNK_SIZE_X - (negativeChunkOffsetX ? 1 : 0);
        int chunkZ = z / Chunk::CHUNK_SIZE_Z - (negativeChunkOffsetZ ? 1 : 0);

        int blockX = (x - Chunk::CHUNK_SIZE_X * chunkX) % Chunk::CHUNK_SIZE_X;
        int blockZ = (z - Chunk::CHUNK_SIZE_Z * chunkZ) % Chunk::CHUNK_SIZE_Z;

        int deltaX = chunkX - this->centerChunkX;
        int deltaZ = chunkZ - this->centerChunkZ;

        int chunkIndex = this->getChunkVectorIndex(deltaX, deltaZ, this->curRenderDistance);

        this->loadedChunks[chunkIndex]->setBlock(blockX, y, blockZ, block);
    }

    void ChunkManager::render(GL::GLFWContext& context, GL::ShaderProgram& shader, const BlockAtlas& blockAtlas, const glm::mat4& viewProjMat) {
        shader.use();

        blockAtlas.bindAndSetTexture(shader);
        blockAtlas.setUniforms(shader);

        shader.setMat4("viewProjMatrix", viewProjMat);

        for(const auto& chunkPtr : this->loadedChunks) {
            if(!chunkPtr) {
                continue;
            }

            chunkPtr->render(context, shader, blockAtlas, this);
        }

        blockAtlas.unbindTexture();
    }

    int ChunkManager::getChunkVectorIndex(int xOffset, int zOffset, int renderDistance) const {
        int lengthInChunks = 2 * renderDistance + 1;

        int xIndex = xOffset + renderDistance;
        int zIndex = zOffset + renderDistance;

        return zIndex * lengthInChunks + xIndex;
    }

    std::shared_ptr<Chunk> ChunkManager::createAndPopulateChunk(int chunkX, int chunkZ) {
        auto chunkPtr = std::make_shared<Chunk>(chunkX, chunkZ);

        for(int i = 0; i < 16; i++) {
            for(int j = 0; j < 16; j++) {
                float noiseX = 0.05f * (float)(Chunk::CHUNK_SIZE_X * chunkX + i);
                float noiseZ = 0.05f * (float)(Chunk::CHUNK_SIZE_Z * chunkZ + j);

                float h = 16.0f + 8.0f * stb_perlin_noise3(noiseX, 0.0f, noiseZ, 0, 0, 0);

                for(int k = 0; k <= (int)h; k++) {
                    chunkPtr->setBlock(i, k, j, k == (int)h ? Blocks::GRASS : Blocks::DIRT);
                }
            }
        }

        return chunkPtr;
    }
}