// This is the internal engine Simpleton header
#pragma once

#include "../managers/cWindowManager.hpp"
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

            std::unique_ptr<CWindowManager> mWindowManager;
            
        protected:
            virtual void OnInit();
            virtual void OnUpdate();
            virtual void OnDestroy();

        private:
            // if false - breaks external engine loop in Run()
            bool mIsRunning = true;

            struct AppImpl;
            std::unique_ptr<AppImpl> mpInternal;
    };
}