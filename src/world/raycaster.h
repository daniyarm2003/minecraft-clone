#ifndef RAYCASTER_H
#define RAYCASTER_H

#include "chunks/chunk_manager.h"
#include <glm/glm.hpp>

namespace World {
    struct RaycastHit {
    public:
        RaycastHit(const glm::vec3& rayStart, const glm::vec3& rayDirection);
        RaycastHit(const glm::vec3& rayStart, const glm::vec3& rayDirection, const glm::ivec3& blockPos, const glm::ivec3& prevBlockPos);

        operator bool () const;

        const glm::vec3& getRayStart() const;
        const glm::vec3& getRayDirection() const;

        const glm::ivec3& getBlockPosition() const;
        const glm::ivec3& getPreviousBlockPosition() const;

    private:
        bool isHit;

        glm::vec3 rayStart;
        glm::vec3 rayDirection;

        glm::ivec3 blockPos;
        glm::ivec3 prevBlockPos;
    };

    class Raycaster {
    public:
        const RaycastHit raycast(const Chunks::ChunkManager& chunkManager, const glm::vec3& rayStart, const glm::vec3& rayDirection) const;
    };
}

#endif // RAYCASTER_H