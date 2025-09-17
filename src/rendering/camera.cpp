#include "camera.h"

namespace Rendering {
    Camera::Camera(Utils::Transform transform, float fov) : transform(transform), fov(fov) {}

    const Utils::Transform& Camera::getTransform() const {
        return transform;
    }

    void Camera::setTransform(const Utils::Transform& transform) {
        this->transform = transform;
    }

    const glm::vec3& Camera::getPosition() const {
        return this->transform.getPosition();
    }

    void Camera::setPosition(const glm::vec3& position) {
        this->transform.setPosition(position);
    }

    const glm::quat& Camera::getRotation() const {
        return this->transform.getRotation();
    }

    void Camera::setRotation(const glm::quat& rotation) {
        this->transform.setRotation(rotation);
    }

    float Camera::getFOV() const {
        return this->fov;
    }

    void Camera::setFOV(float fov) {
        this->fov = fov;
    }

    glm::vec3 Camera::getForward() const {
        return this->transform.getRotation() * glm::vec3(0.0f, 0.0f, -1.0f);
    }

    glm::vec3 Camera::getRight() const {
        return this->transform.getRotation() * glm::vec3(1.0f, 0.0f, 0.0f);
    }

    glm::mat4 Camera::getViewProjectionMatrix(float aspectRatio, float nearPlane, float farPlane) const {
        glm::mat4 projection = glm::perspective(glm::radians(this->fov), aspectRatio, nearPlane, farPlane);

        glm::vec3 forward = this->getForward();
        glm::vec3 right = this->getRight();
        glm::vec3 up = glm::cross(right, forward);

        glm::mat4 view = glm::lookAt(this->transform.getPosition(), this->transform.getPosition() + forward, up);

        return projection * view;
    }
}