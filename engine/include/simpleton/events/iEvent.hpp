#pragma once

#include <string>

namespace Simpleton {
    class IEvent {
        public:
            virtual ~IEvent() = default;
            std::string mType;
    };
}