#pragma once

#include "../util/cLog.hpp"
#include "../core/cDependencyResolver.hpp"

#include "simpleton/managers/iInputManager.hpp"
#include "./iManagerInternal.hpp"
#include "simpleton/events/iEventHandler.hpp"
#include "simpleton/events/iEvent.hpp"

#include <map>

typedef struct GLFWwindow GLFWwindow;

namespace Simpleton {
    class CInputManager : public IInputManager, public IManagerInternal, public IEventHandler 
    {
        public:
            ~CInputManager() {};

            bool OnInit(std::shared_ptr<CDependencyResolver> depResolver);
            void OnDestroy();

            void AddBinding(int key, std::function<void()> func) override; 
            void RemoveBinding(int key) override; 

            void HandleEvent(const IEvent &event) override;

            virtual double GetMouseX() override { return mouseX; };
            virtual double GetMouseY() override { return mouseY; };

        private:
            double mouseX = 0, mouseY = 0;

            std::shared_ptr<CLogger> mpLogger;
            GLFWwindow *mWindow;

            // Store input binding from game before manager is initialized
            std::map<int, std::function<void()>> mStoredBindings;
            std::map<int, std::function<void()>> mBindings;
    };
}