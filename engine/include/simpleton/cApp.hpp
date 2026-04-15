#pragma once

#include "simpleton/managers/iWindowManager.hpp"
#include "simpleton/managers/iInputManager.hpp"
#include <memory>
#include <string>

namespace Simpleton {
    class CApp {
        public:
            CApp() = delete;
            CApp(unsigned int wWidth, unsigned int wHeight, std::string windowName);
            virtual ~CApp();

            void Run();
            // Set flag to break engine internal and external loops in Run()
            void Shutdown();
            // Set flag to break engine internal loop in Run()
            void Restart();

            std::shared_ptr<IWindowManager> mWindowManager;
            std::shared_ptr<IInputManager> mInputManager;
            
        protected:
            virtual void OnInit();
            virtual void OnUpdate();
            virtual void OnDestroy();

        private:
            struct AppImpl;
            std::unique_ptr<AppImpl> mpImplem;
    };
}