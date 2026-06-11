#pragma once

#include <array>

namespace Simpleton {
    template <typename T>
    struct TexVert {
        T x, y;
        float u, v;
    };

    template <typename T>
    TexVert<T> GetCenterPoint(const TexVert<T> *verts, int count) {
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