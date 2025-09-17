#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include "../utils/transform.h"

namespace Rendering {
    class Camera {
    public:
        Camera(Utils::Transform transform = Utils::Transform(), float fov = 45.0f);

        const Utils::Transform& getTransform() const;
        void setTransform(const Utils::Transform& transform);

        const glm::vec3& getPosition() const;
        void setPosition(const glm::vec3& position);

        const glm::quat& getRotation() const;
        void setRotation(const glm::quat& rotation);

        float getFOV() const;
        void setFOV(float fov);

        glm::vec3 getForward() const;
        glm::vec3 getRight() const;
        
        glm::mat4 getViewProjectionMatrix(float aspectRatio, float nearPlane, float farPlane) const;

    private:
        Utils::Transform transform;
        float fov;
    };
}

#endif // CAMERA_H