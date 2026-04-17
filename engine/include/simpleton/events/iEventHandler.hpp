#pragma once

#include "./iEvent.hpp"

namespace Simpleton {
    class IEventHandler {
        public:
            virtual void HandleEvent(const IEvent &event) = 0;
    };
}