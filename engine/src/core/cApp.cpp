#include <simpleton/core/cApp.hpp>
#include "../util/cLog.hpp"

namespace Simpleton {
    struct CApp::AppImpl {
        cLogger logger;
    };

    CApp::CApp() {};

    CApp::~CApp() {};

    void CApp::Run() {
        OnInit();
        for(int i = 0; i < 10; i++) {
            pInternal->logger << 5 << "test" << 1.0f << "\n";
            OnUpdate();
        }
        OnDestroy();
    }
}