#include <array>

#include "../cResourceManager.hpp"
#include "../../resources/cOpenGLTexture.hpp"

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

        // Shader used for drawing untextured primitives
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

        // Shader used for drawing textured primitives
        mPrimitiveTexturedShader.AddShaderSource(ShaderType::VertexShader, "#version 330 core\n"
            "layout (location = 0) in ivec2 aPos;\n"
            "layout (location = 1) in vec2 aTexCoord;\n"
            "out vec2 TexCoord;\n"
            "uniform mat4 vertMat;"
            "void main()\n"
            "{\n"
            "   gl_Position = vertMat * vec4(vec2(aPos), 1.0, 1.0);\n"
            "   TexCoord = aTexCoord;\n"
            "}\0");
        mPrimitiveTexturedShader.AddShaderSource(ShaderType::FragmentShader, "#version 330 core\n"
            "out vec4 FragColor;\n"
            "in vec2 TexCoord;\n"
            "uniform sampler2D texture0;\n"
            "void main()\n"
            "{\n"
            "    FragColor = texture(texture0, TexCoord);\n"
            "}\0");
        if(!mPrimitiveTexturedShader.Compile()) {
            *mpLogger << "\nOGL Renderer init ERROR: Failed to compile primitive textured shader!\n";
            *mpLogger << mPrimitiveTexturedShader.GetErrorLog() << "\n\n";
        }

        // Shader used for drawing circles
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
            "uniform int lineWidth;\n"
            "uniform vec3 CenterPointRadius;\n"
            "void main()\n"
            "{\n"
            "   float lengthFromCenter = length(gl_FragCoord.xy - CenterPointRadius.xy);\n"
            "   if(lineWidth == 0) {\n"
            "       FragColor = lengthFromCenter < CenterPointRadius.z ? Color : vec4(0.0);\n"
            "   } else {\n"
            "       FragColor = ((lengthFromCenter < CenterPointRadius.z) && (lengthFromCenter >= CenterPointRadius.z - lineWidth)) ? Color : vec4(0.0);\n"
            "   }\n"
            "}\0");
        if(!mCircleShader.Compile()) {
            *mpLogger << "\nOGL Renderer init ERROR: Failed to compile cirlce shader!\n";
            *mpLogger << mCircleShader.GetErrorLog() << "\n\n";
        }

        mPrimitiveMeshRenderer.Init();

        mIsInitialized = true;
        return true;
    }
    void COpenGLRenderManager::OnDestroy() {
        *mpLogger << "Render Manager destroy...\n";
        mPrimitiveShader.Destroy();
        mCircleShader.Destroy();
        mPrimitiveMeshRenderer.Destroy();
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

        mPrimitiveMeshRenderer.Draw(triangle.GetPoints().data(), 3, RenderMode::RenderTriangle);
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

        mPrimitiveMeshRenderer.Draw(rect.GetVerts().data(), indeces, 4, 6, RenderMode::RenderTriangle);
    }

    // if 'lineWIdth' == 0 - call FillCircle, if line is specified - render DrawCircle
    void COpenGLRenderManager::RenderCircleInternal(Circle<int> circle, Color<float> color, int lineWidth) {
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
        mCircleShader.SetUniform("lineWidth", lineWidth);

        mCircleShader.SetUniform("CenterPointRadius", static_cast<float>(circle.center.x), static_cast<float>(circle.center.y),
            static_cast<float>(circle.r));

        SetGlobalUniforms(mCircleShader.GetProgId());

        mPrimitiveMeshRenderer.Draw(rect, indeces, 4, 6, RenderMode::RenderTriangle);
    }

    void COpenGLRenderManager::FillCircle(Circle<int> circle, Color<float> color) {
        RenderCircleInternal(circle, color, 0);
    }

    void COpenGLRenderManager::DrawCircle(Circle<int> circle, Color<float> color, int lineWidth) {
        RenderCircleInternal(circle, color, lineWidth);
    }

    void COpenGLRenderManager::DrawLines(Point<int> points[], unsigned int pointCount, Color<float> color, int lineWidth) {
        glLineWidth(lineWidth);
        CDependencyResolver* depResolver = reinterpret_cast<CDependencyResolver*>(glfwGetWindowUserPointer(mWindow));
        Point<unsigned int> windowSize = depResolver->GetWindowManager()->GetWindowSize();
        glm::mat4 orthoMat = glm::ortho(0.0f, static_cast<float>(windowSize.x), static_cast<float>(windowSize.y), 1.0f);

        mPrimitiveShader.Bind();
        mPrimitiveShader.SetUniform("Color", color.r, color.g, color.b, color.a);
        mPrimitiveShader.SetUniform("vertMat", orthoMat);

        mPrimitiveMeshRenderer.Draw(points, pointCount, RenderMode::RenderLines);
        glLineWidth(1);
    }

    void COpenGLRenderManager::DrawTexturedRect(Rect<int> rect, std::string textureName, float rotation) {
        CDependencyResolver* depResolver = reinterpret_cast<CDependencyResolver*>(glfwGetWindowUserPointer(mWindow));
        std::shared_ptr<CResourceManager> resourceManager = depResolver->GetResourceManager();
        Point<unsigned int> windowSize = depResolver->GetWindowManager()->GetWindowSize();
        glm::mat4 orthoMat = glm::ortho(0.0f, static_cast<float>(windowSize.x), static_cast<float>(windowSize.y), 1.0f);

        std::shared_ptr<COpenGLTexture> texture = std::dynamic_pointer_cast<COpenGLTexture>(resourceManager->GetTexture(textureName));
        texture->Bind();

        unsigned int indeces[] = {0, 1, 3, 1, 2, 3};

        mPrimitiveTexturedShader.Bind();

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

        mPrimitiveTexturedShader.SetUniform("vertMat", orthoMat * vertMat);

        SetGlobalUniforms(mPrimitiveTexturedShader.GetProgId());

        // TO DO: Add texture verts to data
        // TO DO: Add texture verts to VBO to access in shader
        mPrimitiveMeshRenderer.Draw(rect.GetVerts().data(), indeces, 4, 6, RenderMode::RenderTriangle);
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