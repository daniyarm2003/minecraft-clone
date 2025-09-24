#include "raycaster.h"
#include <glm/gtx/norm.hpp>

namespace World {
    RaycastHit::RaycastHit(const glm::vec3& rayStart, const glm::vec3& rayDirection) 
        : isHit(false), rayStart(rayStart), rayDirection(rayDirection) {}

    RaycastHit::RaycastHit(const glm::vec3& rayStart, const glm::vec3& rayDirection, const glm::ivec3& blockPos, const glm::ivec3& prevBlockPos) 
        : isHit(true), rayStart(rayStart), rayDirection(rayDirection), blockPos(blockPos), prevBlockPos(prevBlockPos) {}

    RaycastHit::operator bool() const {
        return this->isHit;
    }

    const glm::vec3& RaycastHit::getRayStart() const {
        return this->rayStart;
    }

    const glm::vec3& RaycastHit::getRayDirection() const {
        return this->rayDirection;
    }

    const glm::ivec3& RaycastHit::getBlockPosition() const {
        return this->blockPos;
    }

    const glm::ivec3& RaycastHit::getPreviousBlockPosition() const {
        return this->prevBlockPos;
    }

    const RaycastHit Raycaster::raycast(const Chunks::ChunkManager& chunkManager, const glm::vec3& rayStart, const glm::vec3& rayDirection, float distLimit) const {
        glm::vec3 prevPos = rayStart;
        glm::vec3 curPos = rayStart;

        float scaledDistLimit = distLimit * Chunks::Chunk::BLOCK_SIZE_FLOAT;

        while(chunkManager.isPosLoaded(curPos) && glm::length2(curPos - rayStart) <= scaledDistLimit * scaledDistLimit) {
            glm::ivec3 curBlockPos = chunkManager.getBlockPosFromPos(curPos);

            if(chunkManager.getBlock(curBlockPos).isSolid()) {
                glm::ivec3 prevBlockPos = chunkManager.getBlockPosFromPos(prevPos);

                return RaycastHit(rayStart, rayDirection, curBlockPos, prevBlockPos);
            }

            prevPos = curPos;
            curPos += 0.05f * Chunks::Chunk::BLOCK_SIZE_FLOAT * rayDirection;
        }

        return RaycastHit(rayStart, rayDirection);
    }
}