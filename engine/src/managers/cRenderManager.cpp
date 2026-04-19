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

    void CRenderManager::Render() {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(mWindow);
    }
}