#pragma once

#include "./iInternalRenderManager.hpp"
#include "../../graphics/opengl/cShader.hpp"
#include "../../graphics/opengl/cPrimitiveMesh.hpp"

#include "simpleton/util/primitives/triangle.hpp"
#include "simpleton/util/primitives/color.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Simpleton {
    class COpenGLRenderManager : public IInternalRenderManager {
        public:
            bool OnInit(std::shared_ptr<CDependencyResolver> depResolver) override;
            void OnDestroy() override;

            void PrepareFrame() override;
            void RenderFrame() override;

            void SetClearColor(float r, float g, float b) override;

            void FillTriangle(Triangle<unsigned int> triangle, Color<float> color) override;

        private:
            GLFWwindow *mWindow;
            CShader mPrimitiveShader;
            CPrimitiveMesh mPrimitiveMesh;
    };
}