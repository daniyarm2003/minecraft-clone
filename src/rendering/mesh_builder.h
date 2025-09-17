#ifndef MESH_BUILDER_H
#define MESH_BUILDER_H

#include "triangle.h"
#include <vector>

namespace Rendering {
    enum class MeshRenderTypeFlags {
        POSITION = 1 << 0,
        COLOR = 1 << 1,
        TEXCOORD = 1 << 2
    };

    class MeshBuilder {
    public:
        MeshBuilder() = default;

        void addTriangle(const Triangle& triangle);
        const std::vector<Triangle>& getTriangles() const;

        void clear();

        std::vector<float> buildVertexData(MeshRenderTypeFlags typeFlags) const;

    private:
        std::vector<Triangle> triangles;
    };
}

#endif // MESH_BUILDER_H