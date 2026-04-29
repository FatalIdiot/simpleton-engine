#pragma once

#include "./point.hpp"

namespace Simpleton {
    template <typename T>
    struct Triangle {
        Point<T> p1;
        Point<T> p2;
        Point<T> p3;
    };
}