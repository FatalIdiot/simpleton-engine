#pragma once

#include "simpleton/events/iEvent.hpp"

const std::string EVENT_TYPE_MOUSERELEASE = "MOUSERELEASE";

namespace Simpleton {
    class CEventMouseRelease : public IEvent {
        public:
            CEventMouseRelease() = delete;
            CEventMouseRelease(int buttonCode) :
                mButtonCode(buttonCode) 
            {
                mType = EVENT_TYPE_MOUSERELEASE;
            };

            int mButtonCode = 0;
    };
}