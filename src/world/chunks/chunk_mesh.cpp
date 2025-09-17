#include "chunk_mesh.h"
#include "chunk.h"

#include "../../utils/math_utils.h"
#include "chunk_manager.h"

namespace World::Chunks {
    ChunkMesh::ChunkMesh() {
        this->chunkVAO.bind();
        this->chunkVBO.bind(GL_ARRAY_BUFFER);

        this->chunkVAO.setVertexIntAttribPointer(0, 3, GL_UNSIGNED_BYTE, sizeof(ChunkMeshVertex), (void*)0);
        this->chunkVAO.setVertexIntAttribPointer(1, 2, GL_UNSIGNED_BYTE, sizeof(ChunkMeshVertex), (void*)offsetof(ChunkMeshVertex, blockTexCoords));

        this->chunkVBO.unbind();
        this->chunkVAO.unbind();
    }

    void ChunkMesh::markDirty() {
        this->dirty = true;
    }

    void ChunkMesh::render(Chunk* chunk, const BlockAtlas& blockAtlas, GL::GLFWContext& context, ChunkManager* chunkManager) {
        if (this->dirty) {
            this->generateMesh(chunk, blockAtlas, chunkManager);
            this->dirty = false;
        }

        if (this->vertices.empty()) {
            return;
        }

        this->chunkVAO.bind();
        this->chunkVBO.bind(GL_ARRAY_BUFFER);

        context.drawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(this->vertices.size()));

        this->chunkVBO.unbind();
        this->chunkVAO.unbind();
    }

    void ChunkMesh::generateMesh(Chunk* chunk, const BlockAtlas& blockAtlas, ChunkManager* chunkManager) {
        this->vertices.clear();

        glm::ivec2 blockTexCoordCache[256][6];
        bool blockTexCoordCachedBlock[256]{};

        for(int x = 0; x < Chunk::CHUNK_SIZE_X; ++x) {
            for(int y = 0; y < Chunk::CHUNK_SIZE_Y; ++y) {
                for(int z = 0; z < Chunk::CHUNK_SIZE_Z; ++z) {
                    const Block& block = chunk->getBlock(x, y, z);
                    glm::ivec3 blockPosition = { x, y, z };
                    
                    if(!block.isSolid()) {
                        continue;
                    }

                    const glm::ivec3 axes[6] = {
                        { 0,  0, -1},
                        { 0,  0,  1},
                        {-1,  0,  0},
                        { 1,  0,  0},
                        { 0, -1,  0},
                        { 0,  1,  0} 
                    };

                    size_t blockId = (size_t)block.getId();

                    if(!blockTexCoordCachedBlock[blockId]) {
                        for(size_t i = 0; i < 6; i++) {
                            const glm::ivec3& axis = axes[i];
                            blockTexCoordCache[blockId][i] = block.getTextureCoordinates(blockAtlas, axis);
                        }

                        blockTexCoordCachedBlock[blockId] = true;
                    }

                    for(size_t i = 0; i < 6; i++) {
                        const glm::ivec3& axis = axes[i];
                        glm::ivec3 boundedAxis = { glm::max(axis.x, 0), glm::max(axis.y, 0), glm::max(axis.z, 0) };

                        glm::ivec3 nextAxis1 = { glm::abs(axis.z), glm::abs(axis.x), glm::abs(axis.y) };

                        glm::ivec3 nextAxis2 = { -axis.y, -axis.z, -axis.x };
                        glm::ivec3 boundedNegativeNextAxis2 = { glm::max(-nextAxis2.x, 0), glm::max(-nextAxis2.y, 0), glm::max(-nextAxis2.z, 0) };

                        glm::ivec3 firstPoint = blockPosition + boundedNegativeNextAxis2 + boundedAxis;

                        glm::ivec3 axisOffsetBlockPosition = blockPosition + axis;

                        const glm::ivec3 points[4] = {
                            firstPoint,
                            firstPoint + nextAxis1,
                            firstPoint + nextAxis1 + nextAxis2,
                            firstPoint + nextAxis2
                        };

                        const glm::ivec2& blockTexCoords = blockTexCoordCache[blockId][i];

                        glm::ivec3 texCoordXAxis = axis.y == 0 ? glm::ivec3(axis.z, 0, -axis.x) : glm::ivec3(1, 0, 0);
                        glm::ivec3 texCoordYAxis = axis.y == 0 ? glm::ivec3(0, 1, 0) : glm::ivec3(0, 0, -axis.y);

                        int minProjX = Utils::Math::idot(points[0], texCoordXAxis);
                        int minProjY = Utils::Math::idot(points[0], texCoordYAxis);

                        for(size_t i = 1; i < 4; i++) {
                            int projTexX = Utils::Math::idot(points[i], texCoordXAxis);
                            int projTexY = Utils::Math::idot(points[i], texCoordYAxis);

                            if(projTexX < minProjX) {
                                minProjX = projTexX;
                            }

                            if(projTexY < minProjY) {
                                minProjY = projTexY;
                            }
                        }

                        glm::ivec2 texCoords[4];

                        for(size_t i = 0; i < 4; i++) {
                            int projXOffset = Utils::Math::idot(points[i], texCoordXAxis) - minProjX;
                            int projYOffset = Utils::Math::idot(points[i], texCoordYAxis) - minProjY;

                            texCoords[i] = blockTexCoords + glm::ivec2(projXOffset, projYOffset);
                        }

                        const size_t indeces[6] = { 0, 1, 2,    2, 3, 0 };

                        if(axisOffsetBlockPosition.x < 0 || axisOffsetBlockPosition.x >= Chunk::CHUNK_SIZE_X
                            || axisOffsetBlockPosition.y < 0 || axisOffsetBlockPosition.y >= Chunk::CHUNK_SIZE_Y
                            || axisOffsetBlockPosition.z < 0 || axisOffsetBlockPosition.z >= Chunk::CHUNK_SIZE_Z) {

                            int neighbourChunkX = chunk->getChunkCoordX() + axis.x;
                            int neighbourChunkZ = chunk->getChunkCoordZ() + axis.z;

                            if(axis.y != 0 || !chunkManager->isChunkLoaded(neighbourChunkX, neighbourChunkZ)) {
                                for(const size_t& index : indeces) {
                                    const glm::ivec3& point = points[index];
                                    const glm::ivec2& texCoord = texCoords[index];

                                    this->vertices.push_back(ChunkMeshVertex {
                                        { (uint8_t)point.x, (uint8_t)point.y, (uint8_t)point.z }, 
                                        { (uint8_t)texCoord.x, (uint8_t)texCoord.y }
                                    });
                                }
                            }
                            else {
                                axisOffsetBlockPosition = { 
                                    (axisOffsetBlockPosition.x + Chunk::CHUNK_SIZE_X) % Chunk::CHUNK_SIZE_X,
                                    (axisOffsetBlockPosition.y + Chunk::CHUNK_SIZE_Y) % Chunk::CHUNK_SIZE_Y,
                                    (axisOffsetBlockPosition.z + Chunk::CHUNK_SIZE_Z) % Chunk::CHUNK_SIZE_Z
                                };

                                auto neighbourChunkPtr = chunkManager->getChunk(neighbourChunkX, neighbourChunkZ);

                                if(!neighbourChunkPtr.lock()->isBlockSolid(axisOffsetBlockPosition)) {
                                    for(const size_t& index : indeces) {
                                        const glm::ivec3& point = points[index];
                                        const glm::ivec2& texCoord = texCoords[index];

                                        this->vertices.push_back(ChunkMeshVertex {
                                            { (uint8_t)point.x, (uint8_t)point.y, (uint8_t)point.z }, 
                                            { (uint8_t)texCoord.x, (uint8_t)texCoord.y }
                                        });
                                    }
                                }
                            }
                        }
                        else if(!chunk->isBlockSolid(axisOffsetBlockPosition)) {
                            for(const size_t& index : indeces) {
                                const glm::ivec3& point = points[index];
                                const glm::ivec2& texCoord = texCoords[index];

                                this->vertices.push_back(ChunkMeshVertex {
                                    { (uint8_t)point.x, (uint8_t)point.y, (uint8_t)point.z }, 
                                    { (uint8_t)texCoord.x, (uint8_t)texCoord.y }
                                });
                            }
                        }
                    }
                }
            }
        }

        this->chunkVBO.bind(GL_ARRAY_BUFFER);
        this->chunkVBO.bufferData(this->vertices.data(), this->vertices.size() * sizeof(ChunkMeshVertex), GL_STATIC_DRAW);
        this->chunkVBO.unbind();
    }
}
