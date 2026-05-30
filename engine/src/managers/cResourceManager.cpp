#include "./cResourceManager.hpp"

namespace Simpleton {
    bool CResourceManager::OnInit() {
        mIsInitialized = true;
        return mIsInitialized;
    };

    void CResourceManager::OnDestroy() {

    }
}