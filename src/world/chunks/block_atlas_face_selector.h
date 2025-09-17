#ifndef BLOCK_ATLAS_FACE_SELECTOR_H
#define BLOCK_ATLAS_FACE_SELECTOR_H

#include <cstdint>
#include <glm/glm.hpp>

#include "block.h"

namespace World::Chunks {
    class BlockAtlasFaceSelector {
    public:
        virtual uint8_t getBlockAtlasFaceId(const Block& block, const glm::ivec3& direction) const = 0;
    };

    class SimpleBlockAtlasFaceSelector : public BlockAtlasFaceSelector {
    public:
        SimpleBlockAtlasFaceSelector(uint8_t faceId);
        uint8_t getBlockAtlasFaceId(const Block& block, const glm::ivec3& direction) const;

    private:
        uint8_t faceId;
    };

    class PillarShapeBlockAtlasFaceSelector : public BlockAtlasFaceSelector {
    public:
        PillarShapeBlockAtlasFaceSelector(uint8_t sideFaceId, uint8_t topFaceId, uint8_t bottomFaceId);
        uint8_t getBlockAtlasFaceId(const Block& block, const glm::ivec3& direction) const;

    private:
        uint8_t sideFaceId, topFaceId, bottomFaceId;
    };
}

#endif // BLOCK_ATLAS_FACE_SELECTOR_H