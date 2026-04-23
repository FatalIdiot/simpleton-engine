#pragma once

#include "simpleton/managers/iManager.hpp"

namespace Simpleton {
    class IRenderManager : private IManager {
        public:
            virtual void SetClearColor(float r, float g, float b) = 0;
    };
}