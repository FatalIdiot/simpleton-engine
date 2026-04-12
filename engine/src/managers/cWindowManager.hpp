#include "simpleton/managers/iWindowManager.hpp"
#include "../util/cLog.hpp"

typedef struct GLFWwindow GLFWwindow;

namespace Simpleton
{
    class CWindowManager : public IWindowManager
    {
    public:
        bool OnInit(std::shared_ptr<CLogger> logger);
        void OnDestroy();

    private:
        std::shared_ptr<CLogger> mpLogger;
        GLFWwindow *mWindow;
    };
}