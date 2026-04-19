#include "./cEventManager.hpp"
#include "./cWindowManager.hpp"

#include "simpleton/events/cEventKeyPress.hpp"

namespace Simpleton {
    void GLFWKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        CDependencyResolver *dependencyResolver = reinterpret_cast<CDependencyResolver *>(glfwGetWindowUserPointer(window));
        if(action == GLFW_PRESS) {
            CEventKeyPress keypressEvent{key};
            dependencyResolver->GetEventManager()->CastEvent(keypressEvent);
        }
    }

    bool CEventManager::OnInit(std::shared_ptr<CDependencyResolver> depResolver) {
        mpLogger = depResolver->GetLogger();
        mWindow = depResolver->GetWindowManager()->GetWindow();
        *mpLogger << "Event Manager init...\n";

        glfwSetKeyCallback(mWindow, GLFWKeyCallback);

        mIsInitialized = true;
        return true;
    }

    void CEventManager::OnDestroy() {
        *mpLogger << "Event Manager destroy...\n";
    }

    void CEventManager::OnUpdate() {
        glfwPollEvents();
    }

    void CEventManager::CastEvent(const IEvent& event) {
        *mpLogger << "Event Manager: casting event of type " << event.mType << "\n";
        for(auto &handler : eventHandlers) {
            handler->HandleEvent(event);
        }
    }

    void CEventManager::RegisterHandler(IEventHandler *handler) {
        *mpLogger << "Event Manager: registering event handler.\n";
        eventHandlers.push_back(handler);
    }
}