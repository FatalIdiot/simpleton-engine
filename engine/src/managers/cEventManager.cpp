#include "./cEventManager.hpp"
#include "./cWindowManager.hpp"

#include "simpleton/events/cEventKeyPress.hpp"
#include "simpleton/events/cEventKeyRelease.hpp"
#include "simpleton/events/cEventMousePress.hpp"
#include "simpleton/events/cEventMouseRelease.hpp"
#include "simpleton/events/cEventWindowClose.hpp"
#include "simpleton/events/cEventMouseMove.hpp"
#include "simpleton/events/cEventMouseScroll.hpp"

namespace Simpleton {
    void GLFWKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        CDependencyResolver *dependencyResolver = reinterpret_cast<CDependencyResolver *>(glfwGetWindowUserPointer(window));
        switch(action) {
            case GLFW_PRESS: {
                    CEventMousePress mousePressEvent{key};
                    dependencyResolver->GetEventManager()->CastEvent(mousePressEvent);
                    break;
                }
            case GLFW_RELEASE: {
                    CEventMouseRelease mouseReleaseEvent{key};
                    dependencyResolver->GetEventManager()->CastEvent(mouseReleaseEvent);
                    break;
                }
            default:
                break;
        }
    }

    void GLFWMouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
    {
        CDependencyResolver *dependencyResolver = reinterpret_cast<CDependencyResolver *>(glfwGetWindowUserPointer(window));
        switch(action) {
            case GLFW_PRESS: {
                    CEventKeyPress buttonPressEvent{button};
                    dependencyResolver->GetEventManager()->CastEvent(buttonPressEvent);
                    break;
                }
            case GLFW_RELEASE: {
                    CEventKeyRelease buttonReleaseEvent{button};
                    dependencyResolver->GetEventManager()->CastEvent(buttonReleaseEvent);
                    break;
                }
            default:
                break;
        }
    }

    void GLFWCursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
    {
        CDependencyResolver *dependencyResolver = reinterpret_cast<CDependencyResolver *>(glfwGetWindowUserPointer(window));
        CEventMouseMove mouseMove{xpos, ypos};
        dependencyResolver->GetEventManager()->CastEvent(mouseMove);
    }

    void GLFWScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
    {
        CDependencyResolver *dependencyResolver = reinterpret_cast<CDependencyResolver *>(glfwGetWindowUserPointer(window));
        CEventMouseScroll mouseScroll{xoffset, yoffset};
        dependencyResolver->GetEventManager()->CastEvent(mouseScroll);
    }

    void GLFWWindowCloseCallback(GLFWwindow* window)
    {
        CDependencyResolver *dependencyResolver = reinterpret_cast<CDependencyResolver *>(glfwGetWindowUserPointer(window));
        CEventWindowClose windowCloseEvent{};
        dependencyResolver->GetEventManager()->CastEvent(windowCloseEvent);
        glfwSetWindowShouldClose(window, GL_FALSE);
    }

    bool CEventManager::OnInit(std::shared_ptr<CDependencyResolver> depResolver) {
        mpLogger = depResolver->GetLogger();
        mWindow = depResolver->GetWindowManager()->GetWindow();
        *mpLogger << "Event Manager init...\n";

        glfwSetKeyCallback(mWindow, GLFWKeyCallback);
        glfwSetMouseButtonCallback(mWindow, GLFWMouseButtonCallback);
        glfwSetCursorPosCallback(mWindow, GLFWCursorPositionCallback);
        glfwSetScrollCallback(mWindow, GLFWScrollCallback);
        glfwSetWindowCloseCallback(mWindow, GLFWWindowCloseCallback);
        

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
        for(auto &handler : eventHandlers) {
            handler->HandleEvent(event);
        }
    }

    void CEventManager::RegisterHandler(IEventHandler *handler) {
        *mpLogger << "Event Manager: registering event handler.\n";
        eventHandlers.push_back(handler);
    }
}