#ifndef CHUNK_H
#define CHUNK_H

#include <array>
#include <glm/glm.hpp>

#include "block.h"
#include "block_atlas.h"
#include "chunk_mesh.h"

namespace World::Chunks {
    class ChunkManager;

    class Chunk {
    public:
        static constexpr int CHUNK_SIZE_X = 16;
        static constexpr int CHUNK_SIZE_Y = 64;
        static constexpr int CHUNK_SIZE_Z = 16;

        static constexpr int BLOCK_SIZE = 5;
        static constexpr float BLOCK_SIZE_FLOAT = (float)BLOCK_SIZE;

        Chunk(int chunkCoordX, int chunkCoordZ);

        const Block& getBlock(const glm::ivec3& blockPos) const;
        const Block& getBlock(int x, int y, int z) const;

        void setBlock(const glm::ivec3& blockPos, const Block& block);
        void setBlock(int x, int y, int z, const Block& block);

        bool isBlockSolid(const glm::ivec3& blockPos) const;
        bool isBlockSolid(int x, int y, int z) const;

        int getChunkCoordX() const;
        int getChunkCoordZ() const;

        void meshMarkDirty();

        void render(GL::GLFWContext& context, GL::ShaderProgram& shader, const BlockAtlas& blockAtlas, ChunkManager* chunkManager);

    private:
        int chunkCoordX, chunkCoordZ;

        std::array<Block, CHUNK_SIZE_X * CHUNK_SIZE_Y * CHUNK_SIZE_Z> blocks;
        std::array<bool, CHUNK_SIZE_X * CHUNK_SIZE_Y * CHUNK_SIZE_Z> solidFlags;

        ChunkMesh mesh;
    };
}

#endif // CHUNK_H