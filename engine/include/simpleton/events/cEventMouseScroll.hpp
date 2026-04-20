#pragma once

#include "simpleton/events/iEvent.hpp"

const std::string EVENT_TYPE_MOUSESCROLL = "MOUSESCROLL";

namespace Simpleton {
    class CEventMouseScroll : public IEvent {
        public:
            CEventMouseScroll() = delete;
            CEventMouseScroll(double x, double y) :
                scrollX(x), scrollY(y) 
            {
                mType = EVENT_TYPE_MOUSESCROLL;
            };

            double scrollX, scrollY;
    };
}