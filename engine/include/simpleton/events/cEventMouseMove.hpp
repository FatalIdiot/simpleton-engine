#pragma once

#include "simpleton/events/iEvent.hpp"

const std::string EVENT_TYPE_MOUSEMOVE = "MOUSEMOVE";

namespace Simpleton {
    class CEventMouseMove : public IEvent {
        public:
            CEventMouseMove() = delete;
            CEventMouseMove(double x, double y) :
                x(x), y(y) 
            {
                mType = EVENT_TYPE_MOUSEMOVE;
            };

            double x, y;
    };
}