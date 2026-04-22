#pragma once

#include "simpleton/events/iEvent.hpp"

const std::string EVENT_TYPE_SECONDPASSED = "SECONDPASSED";

namespace Simpleton {
    class CEventSecondPassed : public IEvent {
        public:
            CEventSecondPassed() 
            {
                mType = EVENT_TYPE_SECONDPASSED;
            };
    };
}