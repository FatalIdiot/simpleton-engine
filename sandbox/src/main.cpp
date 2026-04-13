#include <simpleton/cApp.hpp>
#include <iostream>

class SanboxApp : public Simpleton::CApp {
    public:

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

    SanboxApp SanboxApp{};
    SanboxApp.Run();

    std::cout << "..:: Simpleton Sandbox End ::..\n\n";
    return 0;
}