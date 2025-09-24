#include "glfw_context.h"
#include <stdexcept>

namespace GL {
    GLFWContext::GLFWContext(int width, int height, const char* title) {
        if (!glfwInit()) {
            throw std::runtime_error("Failed to initialize GLFW");
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        this->window = glfwCreateWindow(width, height, title, nullptr, nullptr);

        this->width = width;
        this->height = height;

        if (!this->window) {
            throw std::runtime_error("Failed to create GLFW window");
        }

        this->makeCurrent();

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            throw std::runtime_error("Failed to initialize GLAD");
        }

        glViewport(0, 0, width, height);
    }

    GLFWContext::~GLFWContext() {
        if (this->window) {
            glfwDestroyWindow(this->window);
        }

        glfwTerminate();
    }

    GLFWContext& GLFWContext::getInstance() {
        static GLFWContext instance(defaultWidth, defaultHeight, defaultTitle);
        return instance;
    }

    void GLFWContext::makeCurrent() {
        glfwMakeContextCurrent(this->window);
    }

    void GLFWContext::swapBuffers() {
        glfwSwapBuffers(this->window);
    }

    bool GLFWContext::shouldClose() const {
        return glfwWindowShouldClose(this->window);
    }

    void GLFWContext::pollEvents() {
        glfwPollEvents();
    }

    void GLFWContext::setSwapInterval(int interval) {
        glfwSwapInterval(interval);
    }

    GLFWwindow* GLFWContext::getWindow() const {
        return this->window;
    }

    int GLFWContext::getWidth() const {
        return this->width;
    }

    int GLFWContext::getHeight() const {
        return this->height;
    }

    float GLFWContext::getAspectRatio() const {
        return static_cast<float>(this->width) / static_cast<float>(this->height);
    }

    void GLFWContext::setClearColor(float r, float g, float b, float a) {
        glClearColor(r, g, b, a);
    }

    void GLFWContext::clear(GLbitfield mask) {
        glClear(mask);
    }

    void GLFWContext::drawArrays(GLenum mode, GLint first, GLsizei count) {
        glDrawArrays(mode, first, count);
    }

    void GLFWContext::drawElements(GLenum mode, GLsizei count, GLenum type, const void* indices) {
        glDrawElements(mode, count, type, indices);
    }

    double GLFWContext::getTime() const {
        return glfwGetTime();
    }

    void GLFWContext::enableDepthTest() {
        glEnable(GL_DEPTH_TEST);
    }

    void GLFWContext::disableDepthTest() {
        glDisable(GL_DEPTH_TEST);
    }

    void GLFWContext::setDepthTest(GLenum mode) {
        glDepthFunc(mode);
    }

    void GLFWContext::enableAndSetDepthTest(GLenum mode) {
        this->enableDepthTest();
        this->setDepthTest(mode);
    }

    void GLFWContext::enableBlending() {
        glEnable(GL_BLEND);
    }

    void GLFWContext::disableBlending() {
        glDisable(GL_BLEND);
    }

    void GLFWContext::setBlendFunc(GLenum srcFunc, GLenum destFunc) {
        glBlendFunc(srcFunc, destFunc);
    }

    void GLFWContext::setBlendOperation(GLenum blendOp) {
        glBlendEquation(blendOp);
    }


    void GLFWContext::setCursorMode(int value) {
        glfwSetInputMode(this->window, GLFW_CURSOR, value);
    }

    void GLFWContext::enableFaceCulling() {
        glEnable(GL_CULL_FACE);
    }

    void GLFWContext::disableFaceCulling() {
        glDisable(GL_CULL_FACE);
    }

    void GLFWContext::setCullFrontFace(GLenum face) {
        glFrontFace(face);
    }

    void GLFWContext::setFramebufferSizeCallback(GLFWframebuffersizefun callback) {
        glfwSetFramebufferSizeCallback(this->window, callback);
    }

    void GLFWContext::setKeyCallback(GLFWkeyfun callback) {
        glfwSetKeyCallback(this->window, callback);
    }

    void GLFWContext::setMouseButtonCallback(GLFWmousebuttonfun callback) {
        glfwSetMouseButtonCallback(this->window, callback);
    }

    void GLFWContext::setCursorPosCallback(GLFWcursorposfun callback) {
        glfwSetCursorPosCallback(this->window, callback);
    }
}