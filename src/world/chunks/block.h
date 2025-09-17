#ifndef BLOCK_H
#define BLOCK_H

#include <cstdint>
#include <glm/glm.hpp>

#include "block_atlas.h"

namespace World::Chunks {
    class BlockAtlasFaceSelector;

    class Block {
    public:
        Block();

        Block(uint8_t id, bool solid, std::unique_ptr<BlockAtlasFaceSelector> faceSelector);
        Block(const Block& other);

        uint8_t getId() const;
        bool isSolid() const;

        glm::ivec2 getTextureCoordinates(const BlockAtlas& blockAtlas, const glm::ivec3& direction) const;

    private:
        uint8_t id;
        bool solid;

        uint8_t faceIds[6];
    };
}

#endif // BLOCK_H