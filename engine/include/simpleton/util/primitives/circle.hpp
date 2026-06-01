#pragma once

#include "./point.hpp"

namespace Simpleton {
    template <typename T>
    struct Circle {
        Point<T> center;
        T r;
    };
}