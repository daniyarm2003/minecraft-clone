#ifndef CHUNK_MESH_H
#define CHUNK_MESH_H

#include <vector>
#include <glm/glm.hpp>

#include "../../opengl/vao.h"
#include "../../opengl/vbo.h"
#include "../../opengl/glfw_context.h"

#include "block_atlas.h"

namespace World::Chunks {
    struct ChunkMeshVertex {
        uint8_t position[3];
        uint8_t blockTexCoords[2];
    };

    class Chunk;
    class ChunkManager;

    class ChunkMesh {
    public:
        ChunkMesh();

        void markDirty();
        void render(Chunk* chunk, const BlockAtlas& blockAtlas, GL::GLFWContext& context, ChunkManager* chunkManager);

    private:
        bool dirty = true;
        std::vector<ChunkMeshVertex> vertices;

        GL::VAO chunkVAO;
        GL::VBO chunkVBO;

        void generateMesh(Chunk* chunk, const BlockAtlas& blockAtlas, ChunkManager* chunkManager);
    };
}

#endif // CHUNK_MESH_H