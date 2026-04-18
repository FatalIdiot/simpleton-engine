#pragma once

#include "./iEvent.hpp"

namespace Simpleton {
    class IEventHandler {
        public:
            ~IEventHandler() = default;
            virtual void HandleEvent(const IEvent &event) = 0;
    };
}