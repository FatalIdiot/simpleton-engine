#include "./cOpenGLRenderManager.hpp"
#include "../cWindowManager.hpp"

namespace Simpleton {
    bool COpenGLRenderManager::OnInit(std::shared_ptr<CDependencyResolver> depResolver) {
        mpLogger = depResolver->GetLogger();
        mWindow = depResolver->GetWindowManager()->GetWindow();
        *mpLogger << "Render Manager init...\n";

        SetClearColor(0.0f, 0.0f, 0.0f);

        mPrimitiveShader.AddShaderSource(ShaderType::VertexShader, "#version 330 core\n"
            "layout (location = 0) in vec2 aPos;\n"
            "void main()\n"
            "{\n"
            "   gl_Position = vec4(aPos.x, aPos.y, 1.0, 1.0);\n"
            "}\0");
        mPrimitiveShader.AddShaderSource(ShaderType::FragmentShader, "#version 330 core\n"
            "out vec4 FragColor;\n"
            "uniform vec4 Color;\n"
            "void main()\n"
            "{\n"
            "    FragColor = Color;\n"
            "}\0");
        if(!mPrimitiveShader.Compile()) {
            *mpLogger << "\nOGL Renderer init ERROR: Failed to compile primitive shader!\n";
            *mpLogger << mPrimitiveShader.GetErrorLog() << "\n\n";
        }

        mIsInitialized = true;
        return true;
    }
    void COpenGLRenderManager::OnDestroy() {
        *mpLogger << "Render Manager destroy...\n";
    }

    void COpenGLRenderManager::SetClearColor(float r, float g, float b) {
        glClearColor(r, g, b, 1.0f);
    }

    void COpenGLRenderManager::FillTriangle(Triangle<unsigned int> triangle, Color<float> color) {
        CDependencyResolver* depResolver = reinterpret_cast<CDependencyResolver*>(glfwGetWindowUserPointer(mWindow));
        Triangle<float> triangleScreen = depResolver->GetWindowManager()->CastWindowToScreen(triangle);
        
        mPrimitiveShader.Bind();
        mPrimitiveShader.SetUniform("Color", color.r, color.g, color.b, color.a);

        mPrimitiveMesh.Draw(&triangleScreen, 3);
    }

    void COpenGLRenderManager::PrepareFrame() {
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void COpenGLRenderManager::RenderFrame() {
        glfwSwapBuffers(mWindow);
    }
}