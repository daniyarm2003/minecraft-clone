#include "render_vertex.h"

namespace Rendering {
    RenderVertex::RenderVertex(glm::vec3 position, glm::vec4 color, glm::vec2 texCoord)
        : position(position), color(color), texCoord(texCoord) {}

    const glm::vec3& RenderVertex::getPosition() const {
        return this->position;
    }

    void RenderVertex::setPosition(const glm::vec3& position) {
        this->position = position;
    }

    const glm::vec4& RenderVertex::getColor() const {
        return this->color;
    }

    void RenderVertex::setColor(const glm::vec4& color) {
        this->color = color;
    }

    const glm::vec2& RenderVertex::getTexCoord() const {
        return this->texCoord;
    }

    void RenderVertex::setTexCoord(const glm::vec2& texCoord) {
        this->texCoord = texCoord;
    }
}