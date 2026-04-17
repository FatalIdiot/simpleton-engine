#pragma once

#include "simpleton/managers/iEventManager.hpp"
#include "simpleton/events/iEventHandler.hpp"
#include "simpleton/events/iEvent.hpp"
#include "./iManagerInternal.hpp"
#include "../util/cLog.hpp"

#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Simpleton {
    class CEventManager : public IEventManager, IManagerInternal {
        public:
            bool OnInit(GLFWwindow *window, std::shared_ptr<CLogger> logger);
            void OnDestroy();

            void CastEvent(const IEvent& event);
            void RegisterHandler(IEventHandler *handler);

        private:
            std::shared_ptr<CLogger> mpLogger;
            GLFWwindow *mWindow;

            std::vector<IEventHandler*> eventHandlers;
    };
}