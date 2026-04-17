#include "simpleton/cApp.hpp"
#include "./AppImpl.hpp"

#include "../managers/cWindowManager.hpp"
#include "../managers/cEventManager.hpp"
#include "../managers/cInputManager.hpp"
#include "../managers/cRenderManager.hpp"
#include "../util/cLog.hpp"

namespace Simpleton {
    CApp::CApp(unsigned int wWidth, unsigned int wHeight, std::string windowName) {
        mpImplem = std::make_unique<AppImpl>();
        mpImplem->wWidth = wWidth;
        mpImplem->wHeight = wHeight;
        mpImplem->windowName = windowName;

        mpImplem->windowManager = std::make_shared<CWindowManager>();
        mWindowManager = mpImplem->windowManager;

        mpImplem->eventManager = std::make_shared<CEventManager>();
        mEventManager = mpImplem->eventManager;

        mpImplem->inputManager = std::make_shared<CInputManager>();
        mInputManager = mpImplem->inputManager;

        mpImplem->renderManager = std::make_shared<CRenderManager>();
        mRenderManager = mpImplem->renderManager;
    };
    CApp::~CApp() {};

    void CApp::OnInit() {
        mpImplem->logger = std::make_shared<CLogger>();
        *mpImplem->logger << "Engine init...\n";

        mpImplem->windowManager->OnInit(mpImplem->wWidth, mpImplem->wHeight, mpImplem->windowName, mpImplem->logger);
        mpImplem->eventManager->OnInit(mpImplem->logger);
        mpImplem->inputManager->OnInit(mpImplem->windowManager->GetWindow(), mpImplem->logger);
        mpImplem->renderManager->OnInit(mpImplem->logger, mpImplem->windowManager->GetWindow());
    };

    void CApp::OnDestroy() {
        *mpImplem->logger << "Engine destroy...\n";
        mpImplem->renderManager->OnDestroy();
        mpImplem->inputManager->OnDestroy();
        mpImplem->eventManager->OnDestroy();
        mpImplem->windowManager->OnDestroy();
    };

    void CApp::OnUpdate() {
        mpImplem->engineTicks++;
        mpImplem->inputManager->PollEvents();
        mpImplem->renderManager->Render();
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