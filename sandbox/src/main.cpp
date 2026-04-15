#include <simpleton/cApp.hpp>
#include <iostream>

class SandboxApp : public Simpleton::CApp {
    public:
        SandboxApp(unsigned int wWidth, unsigned int wHeight, std::string windowName)
            : Simpleton::CApp(wWidth, wHeight, windowName) {}

    protected:
        void OnInit() override {
            std::cout << "Game Init!\n";
        }

        void OnUpdate() override {
            std::cout << "Game Update!\n";
        }

        void OnDestroy() override {
            std::cout << "Game Destroy!\n";
        }
};

int main() {
    std::cout << "\n\n..:: Simpleton Sandbox Start ::..\n";

    SandboxApp SandboxApp{800, 600, "Test"};
    std::cout << "Adding bindings\n";
    SandboxApp.mInputManager->AddBinding(256, [&SandboxApp]() -> void {
        SandboxApp.Shutdown();
    });
    std::cout << "Finished adding bindings\n";
    SandboxApp.Run();

    std::cout << "..:: Simpleton Sandbox End ::..\n\n";
    return 0;
}