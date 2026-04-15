#include "simpleton/cApp.hpp"
#include "../managers/cWindowManager.hpp"
#include "../managers/cInputManager.hpp"
#include "../util/cLog.hpp"

namespace Simpleton {
    struct CApp::AppImpl {
        unsigned int engineTicks = 0;
        // if false - breaks external engine loop in Run()
        bool isExternalRunning = true;
        // if false - breaks internal engine loop in Run() to restart engine
        bool isInternalRunning = true;
        
        // Internal vars for window creation to pass from constructor to manager init
        unsigned int wWidth, wHeight;
        std::string windowName;

        std::shared_ptr<CLogger> logger;
        std::shared_ptr<CWindowManager> windowManager;
        std::shared_ptr<CInputManager> inputManager;
    };

    CApp::CApp(unsigned int wWidth, unsigned int wHeight, std::string windowName) {
        mpImplem = std::make_unique<AppImpl>();
        mpImplem->wWidth = wWidth;
        mpImplem->wHeight = wHeight;
        mpImplem->windowName = windowName;

        mpImplem->windowManager = std::make_shared<CWindowManager>();
        mWindowManager = mpImplem->windowManager;

        mpImplem->inputManager = std::make_shared<CInputManager>(&mStoredInputBindings);
        mInputManager = mpImplem->inputManager;
    };
    CApp::~CApp() {};

    void CApp::OnInit() {
        mpImplem->logger = std::make_shared<CLogger>();
        *mpImplem->logger << "Engine init...\n";

        mpImplem->windowManager->OnInit(mpImplem->wWidth, mpImplem->wHeight, mpImplem->windowName, mpImplem->logger);
        mpImplem->inputManager->OnInit(mpImplem->windowManager->GetWindow(), mpImplem->logger);
    };

    void CApp::OnDestroy() {
        *mpImplem->logger << "Engine destroy...\n";
        mpImplem->windowManager->OnDestroy();
    };

    void CApp::OnUpdate() {
        mpImplem->engineTicks++;
        mpImplem->inputManager->PollEvents();
    }

    void CApp::Shutdown() {
        *mpImplem->logger << "Shutting engine down...\n";
        mpImplem->isExternalRunning = false;
        mpImplem->isInternalRunning = false;
    }

    void CApp::Restart() {
        *mpImplem->logger << "Restarting engine...\n";
        mpImplem->isInternalRunning = false;
    }

    void CApp::Run() {
        // External loop - used to restart engine without killing the process
        while(mpImplem->isExternalRunning) {
            CApp::OnInit();
            OnInit();
            
            while(mpImplem->isInternalRunning) {
                *mpImplem->logger << mpImplem->engineTicks << " ticks" << "\n";
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