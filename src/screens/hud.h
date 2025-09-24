#ifndef HUD_H
#define HUD_H

#include "../opengl/shader.h"
#include "../opengl/texture.h"
#include "../opengl/vao.h"
#include "../opengl/vbo.h"
#include "../opengl/glfw_context.h"

namespace Screens {
    class HUD {
    public:
        HUD();

        void loadResources();
        void render(GL::GLFWContext& context);

    private:
        static constexpr float CROSSHAIR_SIZE = 25.0f;

        GL::ShaderProgram hudSimple;

        GL::VAO hudSimpleVAO;
        GL::VBO hudSimpleVBO;
        
        GL::Texture crosshairTexture;
    };
}

#endif // HUD_H