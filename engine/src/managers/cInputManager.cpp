#include "./cInputManager.hpp"

namespace Simpleton {
    bool CInputManager::OnInit(GLFWwindow *window, std::shared_ptr<CLogger> logger) {
        *mpLogger << "Input Manager init...\n";
        mWindow = window;
        *mpLogger << "Inputs initialized.\n";
        return true;
    };
    void CInputManager::OnDestroy() {
        *mpLogger << "Window Manager destroy...\n";
    };

    void CInputManager::AddBinding(int key, std::function<void()> func) {
        *mpLogger << "Adding binding for key " << key << "\n";
        mBindings[key] = func;
    }

    void CInputManager::RemoveBinding(int key) {
        *mpLogger << "Removing binding for key " << key << "\n";
        std::map<int, std::function<void()>>::iterator element = mBindings.find(key);
        if(element != mBindings.end())
            mBindings.erase(element);
    }

    void CInputManager::PollEvents() {
        glfwPollEvents();

        for (const auto& [key, func] : mBindings) {
            if(glfwGetKey(mWindow, key) == GLFW_PRESS) {
                func();
            }
        }
    }
}