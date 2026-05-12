#pragma once

#include "simpleton/util/primitives/triangle.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Simpleton {
    class CPrimitiveMesh {
        public:
            CPrimitiveMesh();
            ~CPrimitiveMesh();

            // Make draw call for this mesh
            void Draw(const Point<int>* pData, unsigned int pointCount);
            void Draw(const Point<int>* pData, const unsigned int* pIndices, unsigned int pointsCount, unsigned int indicesCount);

        private:
            unsigned int mVBO, mVAO, mEBO;

            // Can't always init in constructor before systems are up, manually init check in functions 
            bool mIsInited = false;
            void Init();
    };
}