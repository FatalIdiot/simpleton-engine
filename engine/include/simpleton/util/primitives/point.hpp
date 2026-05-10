#pragma once

#include <array>

namespace Simpleton {
    template <typename T>
    struct Point {
        T x, y;
    };

    template <typename T>
    Point<T> GetCenterPoint(const Point<T> *points, int count) {
        Point<T> tempPoint = {0, 0};
        for(int i = 0; i < count; i++) {
            tempPoint.x += points[i].x;
            tempPoint.y += points[i].y;
        }
        return {
            tempPoint.x / count,
            tempPoint.y / count
        };
    }
}