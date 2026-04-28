#pragma once

#include "./iInternalRenderManager.hpp"
#include "../../graphics/opengl/cShader.hpp"
#include "../../graphics/opengl/cPrimitiveMesh.hpp"

#include "simpleton/util/primitives/vec2.hpp"

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

            void FillTriangle(Vec2<float> p1, Vec2<float> p2, Vec2<float> p3) override;

        private:
            GLFWwindow *mWindow;
            CShader mPrimitiveShader;
            CPrimitiveMesh mPrimitiveMesh;
    };
}