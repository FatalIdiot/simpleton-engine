#include <simpleton/core/cApp.hpp>
#include "../util/cLog.hpp"

namespace Simpleton {
    struct CApp::AppImpl {
        unsigned int engineTicks = 0;
        bool isRunning = true;
        
        cLogger logger;
    };

    CApp::CApp() {};
    CApp::~CApp() {};

    void CApp::OnInit() {};
    void CApp::OnDestroy() {};

    void CApp::OnUpdate() {
        mpInternal->engineTicks++;
    }

    void CApp::Shutdown() {
        mpInternal->logger << "Shutting engine down...\n";
        mpInternal->isRunning = false;
        mIsRunning = false;
    }

    void CApp::Restart() {
        mpInternal->logger << "Restarting engine...\n";
        mpInternal->isRunning = false;
    }

    void CApp::Run() {
        // External loop - used to restart engine without killing the process
        while(mIsRunning) {
            mpInternal = std::make_unique<AppImpl>();

            CApp::OnInit();
            OnInit();
            for(int i = 0; i < 10; i++) {
                mpInternal->logger << mpInternal->engineTicks << " ticks" << "\n";
                CApp::OnUpdate();
                OnUpdate();
            }
            OnDestroy();
            CApp::OnDestroy();
        }
    }
}