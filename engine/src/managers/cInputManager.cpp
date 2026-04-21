#include "./cInputManager.hpp"
#include "./cWindowManager.hpp"

#include "simpleton/events/iEvent.hpp"
#include "simpleton/events/cEventKeyPress.hpp"
#include "simpleton/events/cEventMouseMove.hpp"

namespace Simpleton {
    bool CInputManager::OnInit(std::shared_ptr<CDependencyResolver> depResolver) {
        mpLogger = depResolver->GetLogger();
        *mpLogger << "Input Manager init...\n";
        mWindow = depResolver->GetWindowManager()->GetWindow();

        *mpLogger << "Inputs initialized.\n";
        mIsInitialized = true;

        for (const auto& [key, func] : mStoredBindings) {
            AddBinding(key, func);
        }
        mStoredBindings.clear();
        *mpLogger << "Input bindings added from storage.\n";

        return true;
    };
    void CInputManager::OnDestroy() {
        *mpLogger << "Window Manager destroy...\n";
    };

    void CInputManager::HandleEvent(const IEvent &event) {
        if(event.mType == EVENT_TYPE_KEYPRESS) {
            const CEventKeyPress *pressEvent = EventCast<CEventKeyPress>(event);
            for (const auto& [key, func] : mBindings) {
                if(pressEvent->mKeyCode == key) {
                    *mpLogger << "Input Manager: firing press event for key " << pressEvent->mKeyCode << ".\n";
                    func();
                }
            }
        } else if(event.mType == EVENT_TYPE_MOUSEMOVE) {
            const CEventMouseMove *mouseMoveEvent = EventCast<CEventMouseMove>(event);
            mouseX = mouseMoveEvent->x;
            mouseY = mouseMoveEvent->y;
        }
    }

    void CInputManager::AddBinding(int key, std::function<void()> func) {
        if(!mIsInitialized) { // if not initialized - store bindings to bind once system is up
            *mpLogger << "Storing binding for key " << key << "\n";
            mStoredBindings[key] = func;
        } else { // if is already initialized - add binding
            *mpLogger << "Adding binding for key " << key << "\n";
            mBindings[key] = func;
        }
    }

    void CInputManager::RemoveBinding(int key) {
        *mpLogger << "Removing binding for key " << key << "\n";
        std::map<int, std::function<void()>>::iterator element = mBindings.find(key);
        if(element != mBindings.end())
            mBindings.erase(element);
    }
}