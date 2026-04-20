#pragma once

#include "simpleton/managers/iManager.hpp"
#include "simpleton/events/iEventHandler.hpp"

namespace Simpleton {
    class IEventManager : public IManager {
        public:
            virtual void RegisterHandler(IEventHandler *handler) = 0;
    };
}