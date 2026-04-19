#pragma once

#include "../util/cLog.hpp"
#include "../core/cDependencyResolver.hpp"

#include "simpleton/managers/iRenderManager.hpp"
#include "./iManagerInternal.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Simpleton {
    class CRenderManager : public IRenderManager, public IManagerInternal {
        public:
            bool OnInit(std::shared_ptr<CDependencyResolver> depResolver);
            void OnDestroy();

            void Render();

        private:
            std::shared_ptr<CLogger> mpLogger;
            GLFWwindow *mWindow;
    };
}