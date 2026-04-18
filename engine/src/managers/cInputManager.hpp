#pragma once

#include "simpleton/managers/iInputManager.hpp"
#include "./iManagerInternal.hpp"

#include "simpleton/events/iEventHandler.hpp"
#include "simpleton/events/iEvent.hpp"

#include "../util/cLog.hpp"

#include <map>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Simpleton {
    class CInputManager : public IInputManager, public IManagerInternal, public IEventHandler 
    {
        public:
            ~CInputManager() {};

            bool OnInit(GLFWwindow *window, std::shared_ptr<CLogger> logger);
            void OnDestroy();

            void AddBinding(int key, std::function<void()> func) override; 
            void RemoveBinding(int key) override; 

            void HandleEvent(const IEvent &event) override;

        private:
            std::shared_ptr<CLogger> mpLogger;
            GLFWwindow *mWindow;

            // Store input binding from game before manager is initialized
            std::map<int, std::function<void()>> mStoredBindings;
            std::map<int, std::function<void()>> mBindings;
    };
}