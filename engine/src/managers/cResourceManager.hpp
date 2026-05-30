#pragma once

#include "./iManagerInternal.hpp"
#include "simpleton/managers/iResourceManager.hpp"

namespace Simpleton
{
    class CResourceManager : public IResourceManager, public IManagerInternal
    {
        public:
            bool OnInit();
            void OnDestroy();
    };
}