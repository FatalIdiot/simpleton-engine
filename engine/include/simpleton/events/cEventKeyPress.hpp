#pragma once

#include "simpleton/events/iEvent.hpp"

const std::string EVENT_TYPE_KEYPRESS = "KEYPRESS";

namespace Simpleton {
    class CEventKeyPress : public IEvent {
        public:
            CEventKeyPress() = delete;
            CEventKeyPress(int keyCode) :
                mKeyCode(keyCode) 
            {
                mType = EVENT_TYPE_KEYPRESS;
            };

            int mKeyCode = 0;
    };
}