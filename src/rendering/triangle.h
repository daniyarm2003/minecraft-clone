#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "render_vertex.h"
#include <array>

namespace Rendering {
    class Triangle {
    public:
        Triangle(const RenderVertex& v1, const RenderVertex& v2, const RenderVertex& v3);

        const std::array<RenderVertex, 3>& getVertices() const;

    private:
        std::array<RenderVertex, 3> vertices;
    };
}

#endif // TRIANGLE_H