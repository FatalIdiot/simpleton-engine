#pragma once

#include "simpleton/managers/iManager.hpp"
#include "simpleton/util/primitives/triangle.hpp"
#include "simpleton/util/primitives/rect.hpp"
#include "simpleton/util/primitives/color.hpp"

namespace Simpleton {
    class IRenderManager : private IManager {
        public:
            virtual void SetClearColor(float r, float g, float b) = 0;
            virtual void SetWireframe(bool enable) = 0;

            virtual void FillTriangle(Triangle<unsigned int> triangle, Color<float> color, float rotation = 0) = 0;
            virtual void FillRect(Rect<unsigned int> rect, Color<float> color, float rotation = 0) = 0;
    };
}