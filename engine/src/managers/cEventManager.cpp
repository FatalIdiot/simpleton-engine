#include "./cEventManager.hpp"
#include "../core/GlfwEnginePointer.hpp"

#include "simpleton/events/cEventKeyPress.hpp"

namespace Simpleton {
    void GLFWKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        GlfwEnginePointer *engineIntern = reinterpret_cast<GlfwEnginePointer *>(glfwGetWindowUserPointer(window));
        if(action == GLFW_PRESS) {
            CEventKeyPress keypressEvent{key};
            engineIntern->mEventManager->CastEvent(keypressEvent);
        }
    }

    bool CEventManager::OnInit(GLFWwindow *window, std::shared_ptr<CLogger> logger) {
        mpLogger = logger;
        mWindow = window;
        *mpLogger << "Event Manager init...\n";

        glfwSetKeyCallback(mWindow, GLFWKeyCallback);

        mIsInitialized = true;
        return true;
    }

    void CEventManager::OnDestroy() {
        *mpLogger << "Event Manager destroy...\n";
    }

    void CEventManager::CastEvent(const IEvent& event) {
        *mpLogger << "Casting event of type " << event.mType << "\n";
    }

    void CEventManager::RegisterHandler(IEventHandler *handler) {
        *mpLogger << "Registering event handler.";
        eventHandlers.push_back(handler);
    }
}