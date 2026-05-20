#pragma once

#include "simpleton/managers/iManager.hpp"
#include "simpleton/util/primitives/triangle.hpp"
#include "simpleton/util/primitives/rect.hpp"
#include "simpleton/util/primitives/color.hpp"
#include "simpleton/util/primitives/circle.hpp"

namespace Simpleton {
    class IRenderManager : private IManager {
        public:
            virtual void SetClearColor(float r, float g, float b) = 0;
            virtual void SetWireframe(bool enable) = 0;

            virtual void FillTriangle(Triangle<int> triangle, Color<float> color, float rotation = 0) = 0;
            virtual void FillRect(Rect<int> rect, Color<float> color, float rotation = 0) = 0;
            virtual void FillCircle(Circle<int> circle, Color<float> color) = 0;
            virtual void DrawCircle(Circle<int> circle, Color<float> color, int lineWIdth = 1) = 0;
            virtual void DrawLines(Point<int> points[], unsigned int pointCount, Color<float> color, int lineWidth = 1) = 0;
    };
}