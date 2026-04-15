#pragma once

#include "simpleton/managers/iWindowManager.hpp"
#include "../util/cLog.hpp"

typedef struct GLFWwindow GLFWwindow;

namespace Simpleton
{
    class CWindowManager : public IWindowManager
    {
        public:
            CWindowManager() {};
            ~CWindowManager() {};

            bool OnInit(unsigned int wWidth, unsigned int wHeight, std::string windowName, std::shared_ptr<CLogger> logger);
            void OnDestroy();

            GLFWwindow* GetWindow();

        private:
            std::shared_ptr<CLogger> mpLogger;
            GLFWwindow *mWindow;
    };
}