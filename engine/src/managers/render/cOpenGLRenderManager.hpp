#pragma once

#include "./iInternalRenderManager.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Simpleton {
    class COpenGLRenderManager : public IInternalRenderManager {
        public:
            bool OnInit(std::shared_ptr<CDependencyResolver> depResolver) override;
            void OnDestroy() override;

            void Render() override;

            void SetClearColor(float r, float g, float b) override;
    };
}