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
            void Draw(const Triangle<float>* pData, unsigned int count);

        private:
            unsigned int mVBO, mVAO;

            // Can't always init in constructor before systems are up, manually init check in functions 
            bool mIsInited = false;
            void Init();
    };
}