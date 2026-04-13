#pragma once

#include "simpleton/managers/iWindowManager.hpp"
#include <memory>

namespace Simpleton {
    class CApp {
        public:
            CApp();
            virtual ~CApp();

            void Run();
            // Set flag to break engine internal and external loops in Run()
            void Shutdown();
            // Set flag to break engine internal loop in Run()
            void Restart();

            std::shared_ptr<IWindowManager> mWindowManager;
            
        protected:
            virtual void OnInit();
            virtual void OnUpdate();
            virtual void OnDestroy();

        private:
            struct AppImpl;
            std::unique_ptr<AppImpl> mpImplem;
    };
}