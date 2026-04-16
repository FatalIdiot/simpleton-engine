#include "./cRenderManager.hpp"

namespace Simpleton {
    bool CRenderManager::OnInit(std::shared_ptr<CLogger> logger, GLFWwindow *window) {
        mpLogger = logger;
        mWindow = window;
        *mpLogger << "Render Manager init...\n";

        mIsInitialized = true;
        return true;
    }
    void CRenderManager::OnDestroy() {
        *mpLogger << "Render Manager destroy...\n";
    }

    void CRenderManager::Render() {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(mWindow);
    }
}