#pragma once

#include <memory>

namespace Simpleton {
    class CLogger;
    class CWindowManager;
    class CEventManager;

    class CDependencyResolver {
        public:
            CDependencyResolver();
            CDependencyResolver(std::shared_ptr<CLogger> logger, std::shared_ptr<CWindowManager> windowManager, std::shared_ptr<CEventManager> eventManager) 
                : mLogger(logger), mWindowManager(windowManager), mEventManager(eventManager) 
                {}

            std::shared_ptr<CLogger> GetLogger() { return mLogger; }
            std::shared_ptr<CWindowManager> GetWindowManager() { return mWindowManager; }
            std::shared_ptr<CEventManager> GetEventManager() { return mEventManager; }

        private:
            std::shared_ptr<CLogger> mLogger = nullptr;
            std::shared_ptr<CWindowManager> mWindowManager = nullptr;
            std::shared_ptr<CEventManager> mEventManager = nullptr;
    };
}