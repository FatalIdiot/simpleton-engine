#include "./cEventManager.hpp"

namespace Simpleton {
    bool CEventManager::OnInit(std::shared_ptr<CLogger> logger) {
        mpLogger = logger;
        *mpLogger << "Event Manager init...\n";

        mIsInitialized = true;
        return true;
    }

    void CEventManager::OnDestroy() {
        *mpLogger << "Event Manager destroy...\n";
    }
}