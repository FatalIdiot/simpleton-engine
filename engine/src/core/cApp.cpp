#include <simpleton/core/cApp.hpp>
#include "../util/cLog.hpp"

namespace Simpleton {
    struct CApp::AppImpl {
        unsigned int engineTicks = 0;
        cLogger logger;
    };

    CApp::CApp() {};
    CApp::~CApp() {};

    void CApp::OnInit() {};
    void CApp::OnDestroy() {};

    void CApp::OnUpdate() {
        pInternal->engineTicks++;
    }

    void CApp::Run() {
        pInternal = std::make_unique<AppImpl>();

        CApp::OnInit();
        OnInit();
        for(int i = 0; i < 10; i++) {
            pInternal->logger << pInternal->engineTicks << " ticks" << "\n";
            CApp::OnUpdate();
            OnUpdate();
        }
        OnDestroy();
        CApp::OnDestroy();
    }
}