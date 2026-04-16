#pragma once

#include "simpleton/managers/iRenderManager.hpp"
#include "./iManagerInternal.hpp"
#include "../util/cLog.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Simpleton {
    class CRenderManager : public IRenderManager, IManagerInternal {
        public:
            bool OnInit(std::shared_ptr<CLogger> logger, GLFWwindow *window);
            void OnDestroy();

            void Render();

        private:
            std::shared_ptr<CLogger> mpLogger;
            GLFWwindow *mWindow;
    };
}