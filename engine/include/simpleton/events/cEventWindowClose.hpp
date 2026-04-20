#pragma once

#include "simpleton/events/iEvent.hpp"

const std::string EVENT_TYPE_WINDOWCLOSE = "WINDOWCLOSE";

namespace Simpleton {
    class CEventWindowClose : public IEvent {
        public:
            CEventWindowClose()
            {
                mType = EVENT_TYPE_WINDOWCLOSE;
            };
    };
}