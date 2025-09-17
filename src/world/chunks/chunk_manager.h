#ifndef CHUNK_MANAGER_H
#define CHUNK_MANAGER_H

#include "chunk.h"
#include "block_atlas.h"
#include "../../opengl/shader.h"

namespace World::Chunks {
    class ChunkManager {
    public:
        int getRenderDistance() const;
        void setRenderDistance(int renderDistance);

        void loadChunks(int centerChunkX, int centerChunkZ);
        void loadChunks(const glm::vec3& pos);

        bool isChunkLoaded(int chunkX, int chunkZ) const;
        std::weak_ptr<Chunk> getChunk(int chunkX, int chunkZ);

        void render(GL::GLFWContext& context, GL::ShaderProgram& shader, const BlockAtlas& blockAtlas, const glm::mat4& viewProjMat);

    private:
        int centerChunkX = 0, centerChunkZ = 0;
        int curRenderDistance = 0;

        std::vector<std::shared_ptr<Chunk>> loadedChunks;

        int getChunkVectorIndex(int chunkOffsetX, int chunkOffsetZ, int renderDistance) const;

        std::shared_ptr<Chunk> createAndPopulateChunk(int chunkX, int chunkZ);
    };
}

#endif // CHUNK_MANAGER_H