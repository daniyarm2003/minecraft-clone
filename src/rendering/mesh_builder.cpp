#include "mesh_builder.h"

namespace Rendering {
    void MeshBuilder::addTriangle(const Triangle& triangle) {
        this->triangles.push_back(triangle);
    }

    const std::vector<Triangle>& MeshBuilder::getTriangles() const {
        return this->triangles;
    }

    void MeshBuilder::clear() {
        this->triangles.clear();
    }

    std::vector<float> MeshBuilder::buildVertexData(MeshRenderTypeFlags typeFlags) const {
        std::vector<float> vertexData;

        for (const auto& triangle : this->triangles) {
            for (const auto& vertex : triangle.getVertices()) {
                if (static_cast<int>(typeFlags) & static_cast<int>(MeshRenderTypeFlags::POSITION)) {
                    const glm::vec3& pos = vertex.getPosition();

                    vertexData.push_back(pos.x);
                    vertexData.push_back(pos.y);
                    vertexData.push_back(pos.z);
                }
                if (static_cast<int>(typeFlags) & static_cast<int>(MeshRenderTypeFlags::COLOR)) {
                    const glm::vec4& color = vertex.getColor();

                    vertexData.push_back(color.r);
                    vertexData.push_back(color.g);
                    vertexData.push_back(color.b);
                    vertexData.push_back(color.a);
                }
                if (static_cast<int>(typeFlags) & static_cast<int>(MeshRenderTypeFlags::TEXCOORD)) {
                    const glm::vec2& texCoord = vertex.getTexCoord();

                    vertexData.push_back(texCoord.x);
                    vertexData.push_back(texCoord.y);
                }
            }
        }

        return vertexData;
    }
}