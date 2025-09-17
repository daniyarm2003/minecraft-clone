#ifndef MATH_UTILS_H
#define MATH_UTILS_H

#include <glm/glm.hpp>

namespace Utils::Math {
    constexpr int idot(const glm::ivec3& a, const glm::ivec3& b) {
        return a.x * b.x + a.y * b.y + a.z * b.z;
    }
}

#endif // MATH_UTILS_H