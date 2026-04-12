#include "./cWindowManager.hpp"

#include <iostream>

namespace Simpleton {
    bool CWindowManager::OnInit() {
        std::cout << "Window Manager Init\n";
        return true;
    }

    void CWindowManager::OnDestroy() {
        std::cout << "Window Manager Destroy\n";
    }
}