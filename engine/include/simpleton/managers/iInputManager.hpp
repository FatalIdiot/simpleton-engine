#pragma once

#include <functional>
#include "simpleton/managers/iManager.hpp"

namespace Simpleton {
    class IInputManager : public IManager {
        public:
            virtual void AddBinding(int key, std::function<void()> func) = 0; 
            virtual void RemoveBinding(int key) = 0; 
    };
}