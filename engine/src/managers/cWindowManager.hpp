#include "simpleton/managers/iWindowManager.hpp"

namespace Simpleton {
    class CWindowManager : public IWindowManager {
        public:
            bool OnInit() override;
            void OnDestroy() override;
    };
}