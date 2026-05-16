#include <iostream>

#include <simpleton/inputDefines.hpp>
#include <simpleton/cApp.hpp>

#include <simpleton/events/iEventHandler.hpp>
#include <simpleton/events/cEventWindowClose.hpp>

const unsigned int WIN_WIDTH = 800;
const unsigned int WIN_HEIGHT = 600;

float rotationAng = 0.0f;
bool rotationEnabled = false;
bool wireframeEnabled = false;

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
            if(rotationEnabled)
                rotationAng += 90.0f * dt;

            mRenderManager->FillTriangle(
                {{0, 0}, {WIN_WIDTH, 0}, {0, WIN_HEIGHT}}, 
                {0.0f, 1.0f, 0.0f, 1.0f}, 
                rotationAng
            );

            mRenderManager->FillRect(
                {{WIN_WIDTH-50, WIN_HEIGHT-50}, 50, 50},
                {1.0f, 0.0f, 0.0f, 1.0f},
                rotationAng
            );

            mRenderManager->FillCircle(
                {{WIN_WIDTH / 2, WIN_HEIGHT / 2}, 50},
                {1.0f, 0.0f, 0.0f, 1.0f}
            );
        }

        void OnDestroy() override {
            std::cout << "Game Destroy!\n";
        }
};

int main() {
    std::cout << "\n\n..:: Simpleton Sandbox Start ::..\n";

    SandboxApp SandboxApp{WIN_WIDTH, WIN_HEIGHT, "Test"};
    
    SandboxApp.mInputManager->AddBinding(KEY_ESCAPE, [&SandboxApp]() -> void {
        SandboxApp.Shutdown();
    });
    SandboxApp.mInputManager->AddBinding(KEY_GRAVE_ACCENT, [&SandboxApp]() -> void {
        SandboxApp.Restart();
    });
    SandboxApp.mInputManager->AddBinding(KEY_LEFT, []() -> void {
        rotationAng -= 10.0f;
    });
    SandboxApp.mInputManager->AddBinding(KEY_RIGHT, []() -> void {
        rotationAng += 10.0f;
    });
    SandboxApp.mInputManager->AddBinding(KEY_SPACE, []() -> void {
        rotationEnabled = !rotationEnabled;
    });
    SandboxApp.mInputManager->AddBinding(KEY_BACKSPACE, [&SandboxApp]() -> void {
        wireframeEnabled = !wireframeEnabled;
        SandboxApp.mRenderManager->SetWireframe(wireframeEnabled);
    });

    SandboxApp.Run();

    std::cout << "..:: Simpleton Sandbox End ::..\n\n";
    return 0;
}