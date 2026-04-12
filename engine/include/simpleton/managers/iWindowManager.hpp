#pragma once

#include "simpleton/managers/iManager.hpp"

namespace Simpleton {
    class IWindowManager : public IManager {
        public:
            ~IWindowManager() = default;
    };
}