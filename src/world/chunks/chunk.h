#ifndef CHUNK_H
#define CHUNK_H

#include <array>
#include <glm/glm.hpp>
#include <unordered_set>

#include "block.h"
#include "block_atlas.h"
#include "chunk_mesh.h"

namespace World::Chunks {
    class ChunkManager;

    struct ChunkModification {
        glm::ivec3 blockPos;
        Block block;
    };

    class Chunk {
    public:
        static constexpr int CHUNK_SIZE_X = 16;
        static constexpr int CHUNK_SIZE_Y = 64;
        static constexpr int CHUNK_SIZE_Z = 16;

        static constexpr int BLOCK_SIZE = 5;
        static constexpr float BLOCK_SIZE_FLOAT = (float)BLOCK_SIZE;

        Chunk(ChunkManager* chunkManager, int chunkCoordX, int chunkCoordZ);

        const Block& getBlock(const glm::ivec3& blockPos) const;
        const Block& getBlock(int x, int y, int z) const;

        void setBlock(const glm::ivec3& blockPos, const Block& block, bool naturalGeneration = true);
        void setBlock(int x, int y, int z, const Block& block, bool naturalGeneration = true);

        int getChunkCoordX() const;
        int getChunkCoordZ() const;

        void meshMarkDirty();

        std::vector<ChunkModification> getChunkModifications() const;

        void render(GL::GLFWContext& context, GL::ShaderProgram& shader, const BlockAtlas& blockAtlas);

    private:
        int chunkCoordX, chunkCoordZ;

        std::array<Block, CHUNK_SIZE_X * CHUNK_SIZE_Y * CHUNK_SIZE_Z> blocks;
        std::unordered_set<int> modifiedBlockCoords;

        ChunkMesh mesh;
        ChunkManager* chunkManager;
    };
}

#endif // CHUNK_H