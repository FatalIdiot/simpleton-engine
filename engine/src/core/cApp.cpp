#include "simpleton/core/cApp.hpp"
#include "../managers/cWindowManager.hpp"
#include "../util/cLog.hpp"

namespace Simpleton {
    struct CApp::AppImpl {
        unsigned int engineTicks = 0;
        bool isRunning = true;
        
        std::shared_ptr<CLogger> logger = std::make_shared<CLogger>();
    };

    CApp::CApp() {};
    CApp::~CApp() {};

    void CApp::OnInit() {
        mpInternal = std::make_unique<AppImpl>();
        *mpInternal->logger << "Engine init...\n";

        mWindowManager = std::make_unique<CWindowManager>();
        static_cast<CWindowManager*>(mWindowManager.get())->OnInit(mpInternal->logger);
    };

    void CApp::OnDestroy() {
        *mpInternal->logger << "Engine destroy...\n";
        static_cast<CWindowManager*>(mWindowManager.get())->OnDestroy();
    };

    void CApp::OnUpdate() {
        mpInternal->engineTicks++;
    }

    void CApp::Shutdown() {
        *mpInternal->logger << "Shutting engine down...\n";
        mpInternal->isRunning = false;
        mIsRunning = false;
    }

    void CApp::Restart() {
        *mpInternal->logger << "Restarting engine...\n";
        mpInternal->isRunning = false;
    }

    void CApp::Run() {
        // External loop - used to restart engine without killing the process
        while(mIsRunning) {
            CApp::OnInit();
            OnInit();
            for(int i = 0; i < 10; i++) {
                *mpInternal->logger << mpInternal->engineTicks << " ticks" << "\n";
                CApp::OnUpdate();
                OnUpdate();
            }

            // Flag engine exit here for now
            Shutdown();
            
            OnDestroy();
            CApp::OnDestroy();
        }
    }
}