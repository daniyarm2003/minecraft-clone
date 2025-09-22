#ifndef CHUNK_MANAGER_H
#define CHUNK_MANAGER_H

#include "chunk.h"
#include "block_atlas.h"
#include "../../opengl/shader.h"

#include <unordered_map>

namespace World::Chunks {
    class ChunkManager {
    public:
        int getRenderDistance() const;
        void setRenderDistance(int renderDistance);

        void loadChunks(int centerChunkX, int centerChunkZ);
        void loadChunks(const glm::vec3& pos);

        bool isChunkLoaded(int chunkX, int chunkZ) const;
        std::weak_ptr<Chunk> getChunk(int chunkX, int chunkZ);

        bool isBlockPosLoaded(const glm::ivec3& blockPos) const;
        bool isBlockPosLoaded(int x, int y, int z) const;

        const Block& getBlock(const glm::ivec3& blockPos) const;
        const Block& getBlock(int x, int y, int z) const;

        void setBlock(const glm::ivec3& blockPos, const Block& block);
        void setBlock(int x, int y, int z, const Block& block);

        void render(GL::GLFWContext& context, GL::ShaderProgram& shader, const BlockAtlas& blockAtlas, const glm::mat4& viewProjMat);

    private:
        int centerChunkX = 0, centerChunkZ = 0;
        int curRenderDistance = 0;

        std::vector<std::shared_ptr<Chunk>> loadedChunks;
        std::unordered_map<uint64_t, std::vector<ChunkModification>> savedChunkModifications;

        int getChunkVectorIndex(int chunkOffsetX, int chunkOffsetZ, int renderDistance) const;

        std::shared_ptr<Chunk> createAndPopulateChunk(int chunkX, int chunkZ);
    };
}

#endif // CHUNK_MANAGER_H