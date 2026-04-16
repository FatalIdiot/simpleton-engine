#include "./cInputManager.hpp"

namespace Simpleton {
    bool CInputManager::OnInit(GLFWwindow *window, std::shared_ptr<CLogger> logger) {
        mpLogger = logger;
        *mpLogger << "Input Manager init...\n";
        mWindow = window;

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

    void CInputManager::PollEvents() {
        glfwPollEvents();

        // if (glfwWindowShouldClose(mWindow)) {
        //     *mpLogger << "Should close\n";
        // }

        for (const auto& [key, func] : mBindings) {
            if(glfwGetKey(mWindow, key) == GLFW_PRESS) {
                func();
            }
        }
    }
}