#include <array>

#include "simpleton/util/primitives/point.hpp"
#include "./cOpenGLRenderManager.hpp"
#include "../cWindowManager.hpp"

#include <glm/glm.hpp>

namespace Simpleton {
    bool COpenGLRenderManager::OnInit(std::shared_ptr<CDependencyResolver> depResolver) {
        mpLogger = depResolver->GetLogger();
        mWindow = depResolver->GetWindowManager()->GetWindow();
        mpDepResolver = depResolver;
        *mpLogger << "Render Manager init...\n";

        SetClearColor(0.0f, 0.0f, 0.0f);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        mPrimitiveShader.AddShaderSource(ShaderType::VertexShader, "#version 330 core\n"
            "layout (location = 0) in ivec2 aPos;\n"
            "uniform mat4 vertMat;"
            "void main()\n"
            "{\n"
            "   gl_Position = vertMat * vec4(vec2(aPos), 1.0, 1.0);\n"
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

        mCircleShader.AddShaderSource(ShaderType::VertexShader, "#version 330 core\n"
            "layout (location = 0) in ivec2 aPos;\n"
            "uniform mat4 orthoMat;"
            "void main()\n"
            "{\n"
            "   gl_Position = orthoMat * vec4(vec2(aPos), 1.0, 1.0);\n"
            "}\0");
        mCircleShader.AddShaderSource(ShaderType::FragmentShader, "#version 330 core\n"
            "out vec4 FragColor;\n"
            "layout(origin_upper_left) in vec4 gl_FragCoord;\n"
            "uniform vec4 Color;\n"
            "uniform vec3 CenterPointRadius;\n"
            "void main()\n"
            "{\n"
            "   FragColor = (length(gl_FragCoord.xy - CenterPointRadius.xy) < CenterPointRadius.z) ? Color : vec4(0.0);\n"
            "}\0");
        if(!mCircleShader.Compile()) {
            *mpLogger << "\nOGL Renderer init ERROR: Failed to compile cirlce shader!\n";
            *mpLogger << mCircleShader.GetErrorLog() << "\n\n";
        }

        mIsInitialized = true;
        return true;
    }
    void COpenGLRenderManager::OnDestroy() {
        *mpLogger << "Render Manager destroy...\n";
        mPrimitiveShader.Destroy();
        mCircleShader.Destroy();
        mPrimitiveMesh.Destroy();
    }

    void COpenGLRenderManager::SetClearColor(float r, float g, float b) {
        glClearColor(r, g, b, 1.0f);
    }
    void COpenGLRenderManager::SetWireframe(bool enable) {
        glPolygonMode(GL_FRONT_AND_BACK, enable ? GL_LINE : GL_FILL);
    }

    void COpenGLRenderManager::FillTriangle(Triangle<int> triangle, Color<float> color, float rotation) {
        CDependencyResolver* depResolver = reinterpret_cast<CDependencyResolver*>(glfwGetWindowUserPointer(mWindow));
        Point<unsigned int> windowSize = depResolver->GetWindowManager()->GetWindowSize();
        glm::mat4 orthoMat = glm::ortho(0.0f, static_cast<float>(windowSize.x), static_cast<float>(windowSize.y), 1.0f);

        mPrimitiveShader.Bind();
        mPrimitiveShader.SetUniform("Color", color.r, color.g, color.b, color.a);

        Point<int> centerPoint = triangle.GetCenterPoint();
        glm::mat4 vertMat(1.0f);
        vertMat = glm::translate(vertMat, glm::vec3(centerPoint.x, centerPoint.y, 0.0f));
        vertMat = glm::rotate(vertMat, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
        vertMat = glm::translate(vertMat, glm::vec3((centerPoint.x * -1), (centerPoint.y * -1), 0.0f));

        mPrimitiveShader.SetUniform("vertMat", orthoMat * vertMat);

        SetGlobalUniforms(mPrimitiveShader.GetProgId());

        mPrimitiveMesh.Draw(triangle.GetPoints().data(), 3, RenderMode::RenderTriangle);
    }

    void COpenGLRenderManager::FillRect(Rect<int> rect, Color<float> color, float rotation) {
        CDependencyResolver* depResolver = reinterpret_cast<CDependencyResolver*>(glfwGetWindowUserPointer(mWindow));
        Point<unsigned int> windowSize = depResolver->GetWindowManager()->GetWindowSize();
        glm::mat4 orthoMat = glm::ortho(0.0f, static_cast<float>(windowSize.x), static_cast<float>(windowSize.y), 1.0f);

        unsigned int indeces[] = {0, 1, 3, 1, 2, 3};

        mPrimitiveShader.Bind();
        mPrimitiveShader.SetUniform("Color", color.r, color.g, color.b, color.a);

        Point<int> centerPoint = rect.GetCenterPoint();
        glm::mat4 vertMat(1.0f);
        vertMat = glm::translate(vertMat, glm::vec3(
            centerPoint.x, 
            centerPoint.y, 
            0.0f
        ));
        vertMat = glm::rotate(vertMat, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
        vertMat = glm::translate(vertMat, glm::vec3(
            centerPoint.x * -1, 
            centerPoint.y * -1, 
            0.0f
        ));

        mPrimitiveShader.SetUniform("vertMat", orthoMat * vertMat);

        SetGlobalUniforms(mPrimitiveShader.GetProgId());

        mPrimitiveMesh.Draw(rect.GetVerts().data(), indeces, 4, 6, RenderMode::RenderTriangle);
    }

    void COpenGLRenderManager::FillCircle(Circle<int> circle, Color<float> color) {
        CDependencyResolver* depResolver = reinterpret_cast<CDependencyResolver*>(glfwGetWindowUserPointer(mWindow));
        Point<unsigned int> windowSize = depResolver->GetWindowManager()->GetWindowSize();
        glm::mat4 orthoMat = glm::ortho(0.0f, static_cast<float>(windowSize.x), static_cast<float>(windowSize.y), 1.0f);

        unsigned int indeces[] = {0, 1, 3, 1, 2, 3};

        Point<int> rect[] = {
            { circle.center.x - circle.r, circle.center.y - circle.r },
            { circle.center.x + circle.r, circle.center.y - circle.r },
            { circle.center.x + circle.r, circle.center.y + circle.r },
            { circle.center.x - circle.r, circle.center.y + circle.r }
        };

        mCircleShader.Bind();
        mCircleShader.SetUniform("Color", color.r, color.g, color.b, color.a);
        mCircleShader.SetUniform("orthoMat", orthoMat);

        mCircleShader.SetUniform("CenterPointRadius", static_cast<float>(circle.center.x), static_cast<float>(circle.center.y),
            static_cast<float>(circle.r));

        SetGlobalUniforms(mCircleShader.GetProgId());

        mPrimitiveMesh.Draw(rect, indeces, 4, 6, RenderMode::RenderTriangle);
    }

    void COpenGLRenderManager::DrawLines(Point<int> points[], unsigned int pointCount, Color<float> color, unsigned int lineWidth) {
        glLineWidth(lineWidth);
        CDependencyResolver* depResolver = reinterpret_cast<CDependencyResolver*>(glfwGetWindowUserPointer(mWindow));
        Point<unsigned int> windowSize = depResolver->GetWindowManager()->GetWindowSize();
        glm::mat4 orthoMat = glm::ortho(0.0f, static_cast<float>(windowSize.x), static_cast<float>(windowSize.y), 1.0f);

        mPrimitiveShader.Bind();
        mPrimitiveShader.SetUniform("Color", color.r, color.g, color.b, color.a);
        mPrimitiveShader.SetUniform("vertMat", orthoMat);

        mPrimitiveMesh.Draw(points, pointCount, RenderMode::RenderLines);
        glLineWidth(1);
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