#ifndef RENDER_VERTEX_H
#define RENDER_VERTEX_H

#include <glm/glm.hpp>

namespace Rendering {
    class RenderVertex {
    public:
        RenderVertex(glm::vec3 position = glm::vec3(), glm::vec4 color = glm::vec4(1.0f), glm::vec2 texCoord = glm::vec2());

        const glm::vec3& getPosition() const;
        void setPosition(const glm::vec3& position);

        const glm::vec4& getColor() const;
        void setColor(const glm::vec4& color);

        const glm::vec2& getTexCoord() const;
        void setTexCoord(const glm::vec2& texCoord);

    private:
        glm::vec3 position;
        glm::vec4 color;
        glm::vec2 texCoord;
    };
}

#endif // RENDER_VERTEX_H