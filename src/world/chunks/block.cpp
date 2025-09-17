#include "block.h"
#include "block_atlas_face_selector.h"

#include <memory.h>

namespace World::Chunks {
    Block::Block() : id(0), solid(false) {}

    Block::Block(uint8_t id, bool solid, std::unique_ptr<BlockAtlasFaceSelector> faceSelector)
        : id(id), solid(solid) {

            const glm::ivec3 axes[6] = {
                { 0,  0, -1},
                { 0,  0,  1},
                {-1,  0,  0},
                { 1,  0,  0},
                { 0, -1,  0},
                { 0,  1,  0} 
            };

            for(const glm::ivec3& axis : axes) {
                int axisDist = glm::max(axis.x + axis.y + axis.z, 0);
                int axisIndex = axisDist | (glm::abs(axis.y) << 1) | (glm::abs(axis.z) << 2);

                this->faceIds[axisIndex] = faceSelector->getBlockAtlasFaceId(*this, axis);
            }
        }

    Block::Block(const Block& other) : id(other.id), solid(other.solid) {
        memcpy(this->faceIds, other.faceIds, 6 * sizeof(uint8_t));
    }

    uint8_t Block::getId() const {
        return this->id;
    }

    bool Block::isSolid() const {
        return this->solid;
    }

    glm::ivec2 Block::getTextureCoordinates(const BlockAtlas& blockAtlas, const glm::ivec3& direction) const {
        int atlasWidth = blockAtlas.getWidthInBlocks();
        int atlasHeight = blockAtlas.getHeightInBlocks();

        int axisDist = glm::max(direction.x + direction.y + direction.z, 0);
        int axisIndex = axisDist | (glm::abs(direction.y) << 1) | (glm::abs(direction.z) << 2);

        uint8_t blockAtlasFaceId = this->faceIds[axisIndex];

        int x = blockAtlasFaceId % atlasWidth;
        int y = atlasHeight - 1 - blockAtlasFaceId / atlasWidth;

        return glm::ivec2(x, y);
    }
}