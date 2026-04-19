#pragma once

#include "../util/cLog.hpp"
#include "../core/cDependencyResolver.hpp"

#include "./iManagerInternal.hpp"
#include "simpleton/managers/iWindowManager.hpp"

typedef struct GLFWwindow GLFWwindow;

namespace Simpleton
{
    class CWindowManager : public IWindowManager, public IManagerInternal
    {
        public:
            CWindowManager() {};
            ~CWindowManager() {};

            bool OnInit(unsigned int wWidth, unsigned int wHeight, std::string windowName, std::shared_ptr<CDependencyResolver> depResolver);
            void OnDestroy();

            GLFWwindow* GetWindow();

        private:
            std::shared_ptr<CLogger> mpLogger;
            GLFWwindow *mWindow;
    };
}