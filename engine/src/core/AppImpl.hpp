// Engine internal impementation
#pragma once

#include "simpleton/cApp.hpp"
#include "./cDependencyResolver.hpp"

#include "../managers/cWindowManager.hpp"
#include "../managers/cEventManager.hpp"
#include "../managers/cInputManager.hpp"
#include "../managers/cRenderManager.hpp"

#include "./AppEventHandler.hpp"

namespace Simpleton {
    struct CApp::AppImpl {
        unsigned int engineTicks = 0;
        // if false - breaks external engine loop in Run()
        bool isExternalRunning = true;
        // if false - breaks internal engine loop in Run() to restart engine
        bool isInternalRunning = true;
        
        // Internal vars for window creation to pass from constructor to manager init
        unsigned int wWidth, wHeight;
        std::string windowName;

        std::shared_ptr<CLogger> logger;
        std::shared_ptr<CWindowManager> windowManager;
        std::shared_ptr<CEventManager> eventManager;
        std::shared_ptr<CInputManager> inputManager;
        std::shared_ptr<CRenderManager> renderManager;

        std::shared_ptr<CDependencyResolver> depResolver;
        CAppEventHandler eventHandler;
    };
}