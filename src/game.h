#ifndef GAME_H
#define GAME_H

#include "opengl/glfw_context.h"
#include "input/input_manager.h"

#include "opengl/vao.h"
#include "opengl/vbo.h"
#include "opengl/shader.h"
#include "opengl/texture.h"

#include "rendering/camera.h"

#include "utils/game_time_tracker.h"

#include "world/chunks/block_atlas.h"
#include "world/chunks/chunk.h"
#include "world/chunks/chunk_manager.h"

#include "world/raycaster.h"

class Game {
public:
    static constexpr int DEFAULT_SCREEN_WIDTH = 800;
    static constexpr int DEFAULT_SCREEN_HEIGHT = 600;
    static constexpr const char* DEFAULT_WINDOW_TITLE = "OpenGL Minecraft Clone";

    Game();

    GL::GLFWContext& getGLFWContext();
    const Input::InputManager& getInputManager() const;

    bool shouldGameRun() const;

    void update();
    void draw();

    static Game& getInstance();

private:
    GL::GLFWContext context;
    Input::InputManager inputManager;

    GL::ShaderProgram testShaderProgram;
    World::Chunks::BlockAtlas blockAtlas;

    std::vector<std::shared_ptr<World::Chunks::Chunk>> testChunks;

    World::Chunks::ChunkManager chunkManager;

    Rendering::Camera camera;
    float storedPitch = 0.0f, storedYaw = 0.0f;

    Utils::GameTimeTracker timeTracker;

    World::Raycaster raycaster;

    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

    static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
    static void keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void mouseCallback(GLFWwindow* window, double xpos, double ypos);
    static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
};

#endif // GAME_H