#include "./cRenderManager.hpp"
#include "./cWindowManager.hpp"

namespace Simpleton {
    bool CRenderManager::OnInit(std::shared_ptr<CDependencyResolver> depResolver) {
        mpLogger = depResolver->GetLogger();
        mWindow = depResolver->GetWindowManager()->GetWindow();
        *mpLogger << "Render Manager init...\n";

        mIsInitialized = true;
        return true;
    }
    void CRenderManager::OnDestroy() {
        *mpLogger << "Render Manager destroy...\n";
    }

    void CRenderManager::SetClearColor(float r, float g, float b) {
        mClearColor = glm::vec3(r, g, b);
    }

    void CRenderManager::Render() {
        glClearColor(mClearColor[0], mClearColor[1], mClearColor[2], 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(mWindow);
    }
}