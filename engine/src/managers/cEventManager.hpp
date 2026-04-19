#pragma once

#include "../util/cLog.hpp"
#include "../core/cDependencyResolver.hpp"

#include "simpleton/managers/iEventManager.hpp"
#include "simpleton/events/iEventHandler.hpp"
#include "simpleton/events/iEvent.hpp"
#include "./iManagerInternal.hpp"

#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Simpleton {
    class CEventManager : public IEventManager, public IManagerInternal {
        public:
            bool OnInit(std::shared_ptr<CDependencyResolver> depResolver);
            void OnDestroy();
            void OnUpdate();

            void CastEvent(const IEvent& event);
            void RegisterHandler(IEventHandler *handler);

        private:
            std::shared_ptr<CLogger> mpLogger;
            GLFWwindow *mWindow;

            std::vector<IEventHandler*> eventHandlers;
    };
}