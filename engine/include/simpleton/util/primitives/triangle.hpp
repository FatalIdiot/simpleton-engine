#pragma once

#include "./point.hpp"
#include <array>

namespace Simpleton {
    template <typename T>
    struct Triangle {
        Point<T> p1;
        Point<T> p2;
        Point<T> p3;

        Point<T> GetCenterPoint() {
            return {
                (p1.x + p2.x + p3.x) / 3,
                (p1.y + p2.y + p3.y) / 3
            };
        }

        std::array<Point<T>, 3> GetPoints() {
            return {
                p1, p2, p3
            };
        }
    };
}