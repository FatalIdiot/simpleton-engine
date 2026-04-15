#pragma once

#include "simpleton/managers/iInputManager.hpp"
#include "../util/cLog.hpp"

#include <map>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Simpleton {
    class CInputManager : public IInputManager {
        public:
            CInputManager() {};
            ~CInputManager() {};

            bool OnInit(GLFWwindow *window, std::shared_ptr<CLogger> logger);
            void OnDestroy();

            void PollEvents();
            void AddBinding(int key, std::function<void()> func) override; 
            void RemoveBinding(int key) override; 

        private:
            std::shared_ptr<CLogger> mpLogger;
            GLFWwindow *mWindow;
            std::map<int, std::function<void()>> mBindings;
    };
}