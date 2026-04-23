#pragma once

#include "../util/cLog.hpp"
#include "../core/cDependencyResolver.hpp"

#include "simpleton/managers/iRenderManager.hpp"
#include "./iManagerInternal.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

namespace Simpleton {
    class CRenderManager : public IRenderManager, public IManagerInternal {
        public:
            bool OnInit(std::shared_ptr<CDependencyResolver> depResolver);
            void OnDestroy();

            void SetClearColor(float r, float g, float b) override;

            void Render();

        private:
            glm::vec3 mClearColor{0.0f, 0.0f, 0.0f};
            std::shared_ptr<CLogger> mpLogger;
            GLFWwindow *mWindow;
    };
}