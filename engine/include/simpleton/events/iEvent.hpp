#pragma once

#include <string>

namespace Simpleton {
    class IEvent {
        public:
            virtual ~IEvent() = default;
            std::string mType;
    };

    template<typename T>
    const T* EventCast(const IEvent& event)
    {
        return dynamic_cast<const T*>(&event);
    }
}