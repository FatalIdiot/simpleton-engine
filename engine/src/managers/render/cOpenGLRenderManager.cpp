#include <array>

#include "simpleton/util/primitives/point.hpp"
#include "./cOpenGLRenderManager.hpp"
#include "../cWindowManager.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Simpleton {
    bool COpenGLRenderManager::OnInit(std::shared_ptr<CDependencyResolver> depResolver) {
        mpLogger = depResolver->GetLogger();
        mWindow = depResolver->GetWindowManager()->GetWindow();
        mpDepResolver = depResolver;
        *mpLogger << "Render Manager init...\n";

        SetClearColor(0.0f, 0.0f, 0.0f);

        mPrimitiveShader.AddShaderSource(ShaderType::VertexShader, "#version 330 core\n"
            "layout (location = 0) in vec2 aPos;\n"
            "uniform vec2 ScreenSize;\n"
            "uniform vec2 CenterPoint;\n"
            "uniform float rotationAng;\n"
            "void main()\n"
            "{\n"
            "   float angle = radians(rotationAng);\n"
            "   float aspect = ScreenSize.x / ScreenSize.y;\n"
            "   float s = sin(angle);\n"
            "   float c = cos(angle);\n"

            "   vec2 newPos = vec2(aPos.x - CenterPoint.x, aPos.y - CenterPoint.y);\n"
            "   newPos.x *= aspect;\n"
            "   newPos = vec2(\n"
            "       newPos.x * c - newPos.y * s,\n"
            "       newPos.y * c + newPos.x * s\n"
            "   );\n"
            "   newPos.x /= aspect;"
            "   newPos = vec2(newPos.x + CenterPoint.x, newPos.y + CenterPoint.y);\n"

            "   gl_Position = vec4(newPos, 1.0, 1.0);\n"
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
    void COpenGLRenderManager::SetWireframe(bool enable) {
        glPolygonMode(GL_FRONT_AND_BACK, enable ? GL_LINE : GL_FILL);
    }

    void COpenGLRenderManager::FillTriangle(Triangle<unsigned int> triangle, Color<float> color, float rotation) {
        CDependencyResolver* depResolver = reinterpret_cast<CDependencyResolver*>(glfwGetWindowUserPointer(mWindow));
        Triangle<float> triangleScreen = depResolver->GetWindowManager()->CastWindowToScreen(triangle);
        
        mPrimitiveShader.Bind();
        mPrimitiveShader.SetUniform("Color", color.r, color.g, color.b, color.a);
        Point<float> centerPoint = triangleScreen.GetCenterPoint();
        mPrimitiveShader.SetUniform("CenterPoint", centerPoint.x, centerPoint.y);
        mPrimitiveShader.SetUniform("rotationAng", rotation);

        SetGlobalUniforms(mPrimitiveShader.GetProgId());

        mPrimitiveMesh.Draw(&triangleScreen, 3);
    }

    void COpenGLRenderManager::FillRect(Rect<unsigned int> rect, Color<float> color, float rotation) {
        CDependencyResolver* depResolver = reinterpret_cast<CDependencyResolver*>(glfwGetWindowUserPointer(mWindow));
        auto windowManager = depResolver->GetWindowManager();

        std::array<Point<unsigned int>, 4> rectVerts = rect.GetVerts();
        Point<float> rectScreenVerts[] = {
            windowManager->CastWindowToScreen(rectVerts[0]),
            windowManager->CastWindowToScreen(rectVerts[1]),
            windowManager->CastWindowToScreen(rectVerts[2]),
            windowManager->CastWindowToScreen(rectVerts[3])
        };
        unsigned int indeces[] = {0, 1, 3, 1, 2, 3};

        mPrimitiveShader.Bind();
        mPrimitiveShader.SetUniform("Color", color.r, color.g, color.b, color.a);
        Point<float> centerPoint = GetCenterPoint<float>(rectScreenVerts, 4);
        mPrimitiveShader.SetUniform("CenterPoint", centerPoint.x, centerPoint.y);
        mPrimitiveShader.SetUniform("rotationAng", rotation);

        SetGlobalUniforms(mPrimitiveShader.GetProgId());

        mPrimitiveMesh.Draw(rectScreenVerts, indeces, 8, 6);
    }

    void COpenGLRenderManager::PrepareFrame() {
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void COpenGLRenderManager::RenderFrame() {
        glfwSwapBuffers(mWindow);
    }

    void COpenGLRenderManager::SetGlobalUniforms(unsigned int shaderProgId) {
        int uniformLocation = glGetUniformLocation(shaderProgId, "ScreenSize");
        Point<unsigned int> winSize = mpDepResolver->GetWindowManager()->GetWindowSize();
        glUniform2f(uniformLocation, static_cast<float>(winSize.x), static_cast<float>(winSize.y));
    }
}