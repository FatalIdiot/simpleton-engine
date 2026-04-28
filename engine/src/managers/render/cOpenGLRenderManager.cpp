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
            "void main()\n"
            "{\n"
            "    FragColor = vec4(1.0, 0.0, 0.0, 1.0);\n"
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

    void COpenGLRenderManager::FillTriangle(unsigned int p1, unsigned int p2, unsigned int p3) {
        // Temp imediate draw

    }

    void COpenGLRenderManager::Render() {
        glClear(GL_COLOR_BUFFER_BIT);



        glfwSwapBuffers(mWindow);
    }
}