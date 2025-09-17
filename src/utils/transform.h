#ifndef UTILS_TRANSFORM_H
#define UTILS_TRANSFORM_H

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <string>

namespace Utils {
    class Transform {
    public:
        Transform(glm::vec3 position = glm::vec3(), glm::quat rotation = glm::identity<glm::quat>(), glm::vec3 scale = glm::vec3(1.0f));

        const glm::vec3& getPosition() const;
        void setPosition(const glm::vec3& position);

        const glm::quat& getRotation() const;
        void setRotation(const glm::quat& rotation);

        const glm::vec3& getScale() const;
        void setScale(const glm::vec3& scale);

        glm::mat4 toMat4() const;

        operator glm::mat4() const;
        operator std::string() const;

    private:
        glm::vec3 position;
        glm::quat rotation;
        glm::vec3 scale;
    };
}

#endif // UTILS_TRANSFORM_H