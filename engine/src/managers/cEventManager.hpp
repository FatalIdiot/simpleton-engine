#pragma once

#include "simpleton/managers/iEventManager.hpp"
#include "./iManagerInternal.hpp"
#include "../util/cLog.hpp"

namespace Simpleton {
    class CEventManager : public IEventManager, IManagerInternal {
        public:
            bool OnInit(std::shared_ptr<CLogger> logger);
            void OnDestroy();

        private:
            std::shared_ptr<CLogger> mpLogger;
    };
}