#include "./cWindowManager.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Simpleton {
    bool CWindowManager::OnInit(unsigned int wWidth, unsigned int wHeight, std::string windowName,
            std::shared_ptr<CDependencyResolver> depResolver) 
    {
        width = wWidth;
        height = wHeight;

        mpLogger = depResolver->GetLogger();
        *mpLogger << "Window Manager init...\n";

        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

        mWindow = glfwCreateWindow(width, height, windowName.c_str(), NULL, NULL);
        if (mWindow == NULL)
        {
            *mpLogger << "Failed to create GLFW window.\n";
            glfwTerminate();
            return false;
        }
        glfwMakeContextCurrent(mWindow);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            *mpLogger << "Failed to initialize GLAD.\n";
            return false;
        }   

        glViewport(0, 0, width, height);

        *mpLogger << "\n";
        *mpLogger << "GL_VENDOR: " << glGetString(GL_VENDOR) << "\n";
        *mpLogger << "GL_RENDERER: " << glGetString(GL_RENDERER) << "\n";
        *mpLogger << "GL_VERSION: " << glGetString(GL_VERSION) << "\n";
        *mpLogger << "GL_SHADING_LANGUAGE_VERSION: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << "\n";
        int monitorsCount;
        GLFWmonitor** monitors = glfwGetMonitors(&monitorsCount);
        if(monitors != NULL) {
            *mpLogger << "Monitors: " << monitorsCount << "\n";
            for (int i = 0; i < monitorsCount; i++) {
                *mpLogger << " - " << glfwGetMonitorName(monitors[i]) << "\n";
            }
        }
        *mpLogger << "Primary monitor: " << glfwGetMonitorName(glfwGetPrimaryMonitor()) << "\n";
        *mpLogger << "\n";

        *mpLogger << "Window initialized.\n";
        mIsInitialized = true;
        return true;
    }

    void CWindowManager::OnDestroy() {
        *mpLogger << "Window Manager destroy...\n";
        glfwDestroyWindow(mWindow);
        glfwTerminate();
    }

    GLFWwindow* CWindowManager::GetWindow() {
        return mWindow;
    }

    Point<float> CWindowManager::CastWindowToScreen(Point<unsigned int> point) {
        return Point<float>{
            (static_cast<float>(point.x) / static_cast<float>(width)) * 2.0f - 1.0f,
            ((static_cast<float>(point.y) / static_cast<float>(height)) * 2.0f - 1.0f) * -1.0f
        };
    }

    Triangle<float> CWindowManager::CastWindowToScreen(Triangle<unsigned int> triangle) {
        return Triangle<float>{
            CastWindowToScreen(triangle.p1),
            CastWindowToScreen(triangle.p2),
            CastWindowToScreen(triangle.p3)
        };
    }

    Rect<float> CWindowManager::CastWindowToScreen(Rect<unsigned int> rect) {
        Rect<float> tempRect{
            CastWindowToScreen(rect.pos),
            static_cast<float>(rect.w) / static_cast<float>(width / 2),
            static_cast<float>(rect.h) / static_cast<float>(height / 2) * -1
        };

        return tempRect;
    }
}