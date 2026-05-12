#pragma once

#include "./iInternalRenderManager.hpp"
#include "../../graphics/opengl/cShader.hpp"
#include "../../graphics/opengl/cPrimitiveMesh.hpp"

#include "simpleton/util/primitives/triangle.hpp"
#include "simpleton/util/primitives/rect.hpp"
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
            void SetWireframe(bool enable) override;

            void FillTriangle(Triangle<int> triangle, Color<float> color, float rotation = 0) override;
            void FillRect(Rect<int> rect, Color<float> color, float rotation = 0) override;

        private:
            std::shared_ptr<CDependencyResolver> mpDepResolver = nullptr;
            GLFWwindow *mWindow;
            CShader mPrimitiveShader;
            CPrimitiveMesh mPrimitiveMesh;

            // Sets common uniforms to shader
            void SetGlobalUniforms(unsigned int shaderProgId);
    };
}