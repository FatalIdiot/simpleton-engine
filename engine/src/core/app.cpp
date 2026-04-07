#include <simpleton/core/app.hpp>
#include "../util/log.hpp"

namespace Simpleton {
    struct CApp::AppImpl {
        Logger logger;
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