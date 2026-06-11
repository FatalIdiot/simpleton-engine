#pragma once

#include "simpleton/util/primitives/triangle.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Simpleton {
    enum RenderMode { RenderTriangle = GL_TRIANGLES, RenderLines = GL_LINES };
    
    class CPrimitiveMeshRender {
        public:
            void Init();
            CPrimitiveMeshRender();
            ~CPrimitiveMeshRender();

            // Make draw call for this mesh
            void Draw(const Point<int>* pData, unsigned int pointCount, RenderMode renderMode);
            void Draw(const Point<int>* pData, const unsigned int* pIndices, unsigned int pointsCount, 
                unsigned int indicesCount, RenderMode renderMode);

            void Destroy();

        private:
            unsigned int mVBO, mVAO, mEBO;
            bool mIsInited = false;
    };
}