#pragma once

#include <array>
#include <iostream>

#include <simpleton/util/primitives/point.hpp>
#include <simpleton/util/primitives/triangle.hpp>

namespace Simpleton {
    template <typename T>
    struct Rect {
        Point<T> pos;
        T w, h;

        std::array<Triangle<T>, 2> ConvertToTriangles() {
            return {
                Triangle<T>{
                    Point<T>{ pos.x, pos.y },
                    Point<T>{ pos.x + w, pos.y },
                    Point<T>{ pos.x, pos.y + h }
                },
                Triangle<T>{
                    Point<T>{ pos.x + w, pos.y },
                    Point<T>{ pos.x, pos.y + h },
                    Point<T>{ pos.x + w, pos.y + h }
                }
            };
        }

        std::array<Point<T>, 4> GetVerts() {
            return {
                Point<T>{ pos.x, pos.y },
                Point<T>{ pos.x + w, pos.y },
                Point<T>{ pos.x + w, pos.y + h },
                Point<T>{ pos.x, pos.y + h }
            };
        }

        Point<T> GetCenterPoint() {
            return {
                pos.x + (w / 2),
                pos.y + (h / 2)
            };
        }
    };
}