#include "simpleton/managers/iWindowManager.hpp"
#include "../util/cLog.hpp"

typedef struct GLFWwindow GLFWwindow;

namespace Simpleton
{
    class CWindowManager : public IWindowManager
    {
    public:
        bool OnInit(CLogger* logger);
        void OnDestroy();

    private:
        CLogger* mpLogger;
        GLFWwindow *mWindow;
    };
}