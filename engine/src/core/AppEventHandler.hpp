#include "simpleton/events/iEventHandler.hpp"

namespace Simpleton {
    class CAppEventHandler : public IEventHandler {
        void HandleEvent(const IEvent &event) override;
    };
}