#include "triangle.h"

namespace Rendering {
    Triangle::Triangle(const RenderVertex& v1, const RenderVertex& v2, const RenderVertex& v3)
        : vertices{v1, v2, v3} {}

    const std::array<RenderVertex, 3>& Triangle::getVertices() const {
        return this->vertices;
    }
}