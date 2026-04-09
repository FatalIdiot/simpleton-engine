#pragma once

#include <memory>

namespace Simpleton {
    class CApp {
        public:
            CApp();
            virtual ~CApp();

            void Run();

        protected:
            virtual void OnInit();
            virtual void OnUpdate();
            virtual void OnDestroy();

        private:
            struct AppImpl;
            std::unique_ptr<AppImpl> pInternal;
    };
}