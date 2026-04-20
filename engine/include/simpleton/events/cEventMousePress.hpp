#pragma once

#include "simpleton/events/iEvent.hpp"

const std::string EVENT_TYPE_MOUSEPRESS = "MOUSEPRESS";

namespace Simpleton {
    class CEventMousePress : public IEvent {
        public:
            CEventMousePress() = delete;
            CEventMousePress(int buttonCode) :
                mButtonCode(buttonCode) 
            {
                mType = EVENT_TYPE_MOUSEPRESS;
            };

            int mButtonCode = 0;
    };
}