#pragma once

#include "simpleton/managers/iManager.hpp"

namespace Simpleton {
    class IRenderManager : private IManager {
        public:
            virtual void SetClearColor(float r, float g, float b) = 0;
            
            virtual void FillTriangle(unsigned int p1, unsigned int p2, unsigned int p3) = 0;
    };
}