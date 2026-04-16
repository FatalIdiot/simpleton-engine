#pragma once

#include "simpleton/managers/iInputManager.hpp"
#include "./iManagerInternal.hpp"
#include "../util/cLog.hpp"

#include <map>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Simpleton {
    class CInputManager : public IInputManager, IManagerInternal 
    {
        public:
            ~CInputManager() {};

            bool OnInit(GLFWwindow *window, std::shared_ptr<CLogger> logger);
            void OnDestroy();

            void PollEvents();
            void AddBinding(int key, std::function<void()> func) override; 
            void RemoveBinding(int key) override; 

        private:
            // bool mIsInitialized = false;

            std::shared_ptr<CLogger> mpLogger;
            GLFWwindow *mWindow;

            // Store input binding from game before manager is initialized
            std::map<int, std::function<void()>> mStoredBindings;
            std::map<int, std::function<void()>> mBindings;
    };
}