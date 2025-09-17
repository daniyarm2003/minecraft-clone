#include "game.h"

#include <iostream>

#include "world/chunks/blocks.h"

Game::Game()
    : context(DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT, DEFAULT_WINDOW_TITLE), blockAtlas(4, 4, 16) {
        this->context.setFramebufferSizeCallback(Game::framebufferSizeCallback);
        this->context.setCursorPosCallback(Game::mouseCallback);
        this->context.setKeyCallback(Game::keyboardCallback);
        this->context.setMouseButtonCallback(Game::mouseButtonCallback);

        this->context.setSwapInterval(1);

        // RAII scope
        {
            GL::Shader vertexShader = GL::Shader::fromFile(GL_VERTEX_SHADER, "assets/shaders/chunk.vs");
            GL::Shader fragmentShader = GL::Shader::fromFile(GL_FRAGMENT_SHADER, "assets/shaders/chunk.fs");

            this->testShaderProgram.attachShader(vertexShader);
            this->testShaderProgram.attachShader(fragmentShader);
            this->testShaderProgram.link();
        }

        this->blockAtlas.loadTextureDataFromFile("assets/textures/blockatlas.png");

        this->context.enableAndSetDepthTest(GL_LESS);
        this->context.enableFaceCulling();
        this->context.setCullFrontFace(GL_CW);

        this->chunkManager.setRenderDistance(5);

        this->camera.setPosition(glm::vec3(0.0f, World::Chunks::Chunk::BLOCK_SIZE_FLOAT * 32.0f, 0.0f));
    }

GL::GLFWContext& Game::getGLFWContext() {
    return this->context;
}

const Input::InputManager& Game::getInputManager() const {
    return this->inputManager;
}

bool Game::shouldGameRun() const {
    return !this->context.shouldClose();
}

void Game::update() {
    this->timeTracker.update(this->context.getTime());

    this->context.pollEvents();
    this->inputManager.updateKeyStates();

    auto camPos = this->camera.getPosition();
    auto camRot = this->camera.getRotation();

    auto camForward = this->camera.getForward();
    auto camRight = this->camera.getRight();

    if(this->inputManager.isKeyPressed(GLFW_KEY_ESCAPE)) {
        this->context.setCursorMode(GLFW_CURSOR_NORMAL);
    }

    float moveSpeed = (this->inputManager.isKeyPressed(GLFW_KEY_R) ? 15.0f : 5.0f) * World::Chunks::Chunk::BLOCK_SIZE_FLOAT;

    if(this->inputManager.isKeyPressed(GLFW_KEY_A)) {
        camPos -= moveSpeed * camRight * (float)this->timeTracker.getDeltaTime();
    }
    else if(this->inputManager.isKeyPressed(GLFW_KEY_D)) {
        camPos += moveSpeed * camRight * (float)this->timeTracker.getDeltaTime();
    }

    if(this->inputManager.isKeyPressed(GLFW_KEY_W)) {
        camPos += moveSpeed * camForward * (float)this->timeTracker.getDeltaTime();
    }
    else if(this->inputManager.isKeyPressed(GLFW_KEY_S)) {
        camPos -= moveSpeed * camForward * (float)this->timeTracker.getDeltaTime();
    }

    if(this->inputManager.isKeyPressed(GLFW_KEY_LEFT_SHIFT)) {
        camPos -= glm::vec3(0.0f, moveSpeed, 0.0f) * (float)this->timeTracker.getDeltaTime();
    }
    else if(this->inputManager.isKeyPressed(GLFW_KEY_SPACE)) {
        camPos += glm::vec3(0.0f, moveSpeed, 0.0f) * (float)this->timeTracker.getDeltaTime();
    }

    if(this->inputManager.isKeyPressed(GLFW_KEY_C)) {
        this->camera.setFOV(15.0f);
    }
    else {
        this->camera.setFOV(45.0f);
    }

    auto mouseDelta = this->inputManager.getMouseDelta();
    float sensitivity = 0.1f * glm::pi<float>();

    float pitchAdjustment = -sensitivity * mouseDelta.y * (float)this->timeTracker.getDeltaTime();
    float yawAdjustment = -sensitivity * mouseDelta.x * (float)this->timeTracker.getDeltaTime();

    this->storedPitch += pitchAdjustment;
    this->storedPitch = glm::clamp(this->storedPitch, -glm::pi<float>() * 0.49f, glm::pi<float>() * 0.49f);

    this->storedYaw += yawAdjustment;

    camRot = glm::quat(glm::vec3(storedPitch, storedYaw, 0.0f));

    this->camera.setPosition(camPos);
    this->camera.setRotation(camRot);

    this->chunkManager.loadChunks(camPos);

    this->inputManager.resetMouseDelta();
}

void Game::draw() {
    this->context.setClearColor(0.1f, 0.75f, 1.0f, 1.0f);
    this->context.clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 cameraTransform = this->camera.getViewProjectionMatrix(this->context.getAspectRatio(), 0.1f, 1000.0f);

    this->chunkManager.render(this->context, this->testShaderProgram, this->blockAtlas, cameraTransform);

    this->context.swapBuffers();
}

Game& Game::getInstance() {
    static Game instance;
    return instance;
}

void Game::framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void Game::keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    Game& game = Game::getInstance();
    if (action == GLFW_PRESS) {
        game.inputManager.onKeyPress(key);
    } 
    else if (action == GLFW_RELEASE) {
        game.inputManager.onKeyRelease(key);
    }
}

void Game::mouseCallback(GLFWwindow* window, double xpos, double ypos) {
    Game& game = Game::getInstance();
    game.inputManager.onMouseMove(xpos, ypos);
}

void Game::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    Game& game = Game::getInstance();
    game.context.setCursorMode(GLFW_CURSOR_DISABLED);
}