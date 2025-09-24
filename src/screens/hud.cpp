#include "hud.h"
#include "../game.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Screens {
    HUD::HUD() : crosshairTexture(GL_TEXTURE_2D) {}

    void HUD::loadResources() {
        // RAII scope
        {
            GL::Shader hudSimpleVertex = GL::Shader::fromFile(GL_VERTEX_SHADER, "assets/shaders/hudSimple.vs");
            GL::Shader hudSimpleFragment = GL::Shader::fromFile(GL_FRAGMENT_SHADER, "assets/shaders/hudSimple.fs");

            this->hudSimple.attachShader(hudSimpleVertex);
            this->hudSimple.attachShader(hudSimpleFragment);
            this->hudSimple.link();
        }

        this->crosshairTexture.bind();
        this->crosshairTexture.loadImage2DFromFile("assets/textures/crosshair.png");

        this->crosshairTexture.setWrapS(GL_REPEAT);
        this->crosshairTexture.setWrapT(GL_REPEAT);

        this->crosshairTexture.setMinFilter(GL_NEAREST);
        this->crosshairTexture.setMagFilter(GL_NEAREST);

        this->crosshairTexture.unbind();

        this->hudSimpleVAO.bind();
        this->hudSimpleVBO.bind(GL_ARRAY_BUFFER);

        this->hudSimpleVAO.setVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
        this->hudSimpleVAO.setVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

        float hudSimpleBufferData[] = {
            0.0f, 0.0f,     0.0f, 0.0f,
            0.0f, 1.0f,     0.0f, 1.0f,
            1.0f, 1.0f,     1.0f, 1.0f,
            1.0f, 1.0f,     1.0f, 1.0f,
            1.0f, 0.0f,     1.0f, 0.0f,
            0.0f, 0.0f,     0.0f, 0.0f,
        };

        this->hudSimpleVBO.bufferData(hudSimpleBufferData, sizeof(hudSimpleBufferData), GL_STATIC_DRAW);

        this->hudSimpleVAO.unbind();
        this->hudSimpleVBO.unbind();

        this->hudSimple.use();
        this->hudSimple.setMat4("hudTransform", glm::ortho(0.0f, (float)Game::DEFAULT_SCREEN_WIDTH, 0.0f, (float)Game::DEFAULT_SCREEN_HEIGHT, -1.0f, 1.0f));
    }

    void HUD::render(GL::GLFWContext& context) {
        context.enableBlending();
        context.setBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        this->hudSimple.use();
        this->hudSimpleVAO.bind();

        this->hudSimple.bindAndSetTexture("componentTexture", this->crosshairTexture);

        glm::mat4 crosshairTransform = glm::identity<glm::mat4>();
        
        crosshairTransform = glm::translate(crosshairTransform, { 
            (Game::DEFAULT_SCREEN_WIDTH - CROSSHAIR_SIZE) / 2.0f,
            (Game::DEFAULT_SCREEN_HEIGHT - CROSSHAIR_SIZE) / 2.0f,
            0.0f 
        });
        
        crosshairTransform = glm::scale(crosshairTransform, { CROSSHAIR_SIZE, CROSSHAIR_SIZE, 1.0f });

        this->hudSimple.setMat4("componentTransform", crosshairTransform);

        context.drawArrays(GL_TRIANGLES, 0, 6);

        this->crosshairTexture.unbind();
        
        this->hudSimpleVAO.unbind();

        context.disableBlending();
    }
}