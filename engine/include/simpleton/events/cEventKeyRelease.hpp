#pragma once

#include "simpleton/events/iEvent.hpp"

const std::string EVENT_TYPE_KEYRELEASE = "KEYRELEASE";

namespace Simpleton {
    class CEventKeyRelease : public IEvent {
        public:
            CEventKeyRelease() = delete;
            CEventKeyRelease(int keyCode) :
                mKeyCode(keyCode) 
            {
                mType = EVENT_TYPE_KEYRELEASE;
            };

            int mKeyCode = 0;
    };
}