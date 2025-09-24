#ifndef GLFW_CONTEXT_H
#define GLFW_CONTEXT_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace GL {
    class GLFWContext {
    public:
        GLFWContext(int width, int height, const char* title);
        ~GLFWContext();

        static GLFWContext& getInstance();

        void makeCurrent();
        void swapBuffers();
        bool shouldClose() const;
        void pollEvents();

        void setSwapInterval(int interval);

        GLFWwindow* getWindow() const;

        int getWidth() const;
        int getHeight() const;

        float getAspectRatio() const;

        void setClearColor(float r, float g, float b, float a);
        void clear(GLbitfield mask);

        void drawArrays(GLenum mode, GLint first, GLsizei count);
        void drawElements(GLenum mode, GLsizei count, GLenum type, const void* indices);

        double getTime() const;

        void enableDepthTest();
        void disableDepthTest();

        void setDepthTest(GLenum mode);
        void enableAndSetDepthTest(GLenum mode);

        void enableBlending();
        void disableBlending();
        void setBlendFunc(GLenum srcFunc, GLenum destFunc);
        void setBlendOperation(GLenum blendOp);

        void setCursorMode(int value);

        void enableFaceCulling();
        void disableFaceCulling();
        void setCullFrontFace(GLenum type);

        void setFramebufferSizeCallback(GLFWframebuffersizefun callback);
        void setKeyCallback(GLFWkeyfun callback);
        void setMouseButtonCallback(GLFWmousebuttonfun callback);
        void setCursorPosCallback(GLFWcursorposfun callback);

    private:
        static constexpr int defaultWidth = 800;
        static constexpr int defaultHeight = 600;
        static constexpr const char* defaultTitle = "OpenGL Window";

        int width, height;

        GLFWwindow* window;

        GLFWContext(const GLFWContext&) = delete;
        GLFWContext& operator=(const GLFWContext&) = delete;
    };
}

#endif // GLFW_CONTEXT_H