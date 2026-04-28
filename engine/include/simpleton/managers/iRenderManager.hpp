#pragma once

#include "simpleton/managers/iManager.hpp"
#include "simpleton/util/primitives/vec2.hpp"

namespace Simpleton {
    class IRenderManager : private IManager {
        public:
            virtual void SetClearColor(float r, float g, float b) = 0;

            virtual void FillTriangle(Vec2<float> p1, Vec2<float> p2, Vec2<float> p3) = 0;
    };
}