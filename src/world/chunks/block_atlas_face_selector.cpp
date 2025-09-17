#include "block_atlas_face_selector.h"

namespace World::Chunks {
    SimpleBlockAtlasFaceSelector::SimpleBlockAtlasFaceSelector(uint8_t faceId) : faceId(faceId) {}

    uint8_t SimpleBlockAtlasFaceSelector::getBlockAtlasFaceId(const Block& block, const glm::ivec3& direction) const {
        return this->faceId;
    }

    PillarShapeBlockAtlasFaceSelector::PillarShapeBlockAtlasFaceSelector(uint8_t sideFaceId, uint8_t topFaceId, uint8_t bottomFaceId) 
        : sideFaceId(sideFaceId), topFaceId(topFaceId), bottomFaceId(bottomFaceId) {}

    uint8_t PillarShapeBlockAtlasFaceSelector::getBlockAtlasFaceId(const Block& block, const glm::ivec3& direction) const {
        if(direction.y == 0) {
            return this->sideFaceId;
        }
        
        return direction.y > 0 ? topFaceId : bottomFaceId;
    }
}