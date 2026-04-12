#include "./cWindowManager.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Simpleton {
    bool CWindowManager::OnInit(std::shared_ptr<CLogger> logger) {
        mpLogger = logger;
        *mpLogger << "Window Manager init...\n";

        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

        mWindow = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
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

        glViewport(0, 0, 800, 600);

        *mpLogger << "Window initialized.\n";
        return true;
    }

    void CWindowManager::OnDestroy() {
        *mpLogger << "Window Manager destroy...\n";
        glfwDestroyWindow(mWindow);
        glfwTerminate();
    }
}