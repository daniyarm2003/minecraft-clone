#include "transform.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>

namespace Utils {
    Transform::Transform(glm::vec3 position, glm::quat rotation, glm::vec3 scale)
        : position(position), rotation(rotation), scale(scale) {}

    const glm::vec3& Transform::getPosition() const {
        return this->position;
    }

    void Transform::setPosition(const glm::vec3& position) {
        this->position = position;
    }

    const glm::quat& Transform::getRotation() const {
        return this->rotation;
    }

    void Transform::setRotation(const glm::quat& rotation) {
        this->rotation = rotation;
    }

    const glm::vec3& Transform::getScale() const {
        return this->scale;
    }

    void Transform::setScale(const glm::vec3& scale) {
        this->scale = scale;
    }

    glm::mat4 Transform::toMat4() const {
        glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), position);
        glm::mat4 rotationMatrix = glm::toMat4(rotation);
        glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), scale);
        
        return translationMatrix * rotationMatrix * scaleMatrix;
    }

    Transform::operator glm::mat4() const {
        return this->toMat4();
    }

    Transform::operator std::string() const {
        return "Position: (" + std::to_string(this->position.x) + ", " + std::to_string(this->position.y) + ", " + std::to_string(this->position.z) + "), " +
               "Rotation: (" + std::to_string(this->rotation.x) + ", " + std::to_string(this->rotation.y) + ", " + std::to_string(this->rotation.z) + ", " + std::to_string(this->rotation.w) + "), " +
               "Scale: (" + std::to_string(this->scale.x) + ", " + std::to_string(this->scale.y) + ", " + std::to_string(this->scale.z) + ")";
    }
}