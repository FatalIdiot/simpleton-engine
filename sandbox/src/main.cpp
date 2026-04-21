#include <iostream>

#include <simpleton/inputDefines.hpp>
#include <simpleton/cApp.hpp>

#include <simpleton/events/iEventHandler.hpp>
#include <simpleton/events/cEventWindowClose.hpp>

class SandboxApp : public Simpleton::CApp, public Simpleton::IEventHandler {
    public:
        SandboxApp(unsigned int wWidth, unsigned int wHeight, std::string windowName)
            : Simpleton::CApp(wWidth, wHeight, windowName) {
                // Register this event handler
                mEventManager->RegisterHandler(this);
            }

        void HandleEvent(const Simpleton::IEvent &event) {
            if(event.mType == EVENT_TYPE_WINDOWCLOSE) {
                Shutdown();
            }
        }

        void OnInit() override {
            std::cout << "Game Init!\n";
        }

        void OnUpdate(float dt) override {
            // std::cout << "Game Update! " << dt << std::endl;
        }

        void OnDestroy() override {
            std::cout << "Game Destroy!\n";
        }
};

int main() {
    std::cout << "\n\n..:: Simpleton Sandbox Start ::..\n";

    SandboxApp SandboxApp{800, 600, "Test"};
    SandboxApp.mInputManager->AddBinding(KEY_ESCAPE, [&SandboxApp]() -> void {
        SandboxApp.Shutdown();
    });
    SandboxApp.mInputManager->AddBinding(KEY_GRAVE_ACCENT, [&SandboxApp]() -> void {
        SandboxApp.Restart();
    });
    SandboxApp.Run();

    std::cout << "..:: Simpleton Sandbox End ::..\n\n";
    return 0;
}