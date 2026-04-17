// Structure that points to systems in internal engine implementation to access them in GLFW functions
#pragma once

#include "../util/cLog.hpp"
#include "../managers/cEventManager.hpp"

namespace Simpleton {
    struct GlfwEnginePointer {
        GlfwEnginePointer() {};
        GlfwEnginePointer(std::shared_ptr<CLogger> logger, std::shared_ptr<CEventManager> mEventManager) 
            : mLogger(logger), mEventManager(mEventManager) 
            {}

        std::shared_ptr<CLogger> mLogger = nullptr;
        std::shared_ptr<CEventManager> mEventManager = nullptr;
    };
}