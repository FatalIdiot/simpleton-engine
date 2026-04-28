#pragma once

#include "../../util/cLog.hpp"
#include "../../core/cDependencyResolver.hpp"

#include "simpleton/managers/iRenderManager.hpp"
#include "../iManagerInternal.hpp"

#include <glm/glm.hpp>

namespace Simpleton {
    class IInternalRenderManager : public IRenderManager, public IManagerInternal {
        public:
            virtual bool OnInit(std::shared_ptr<CDependencyResolver> depResolver) = 0;
            virtual void OnDestroy() = 0;

            virtual void Render() = 0;

        protected:
            std::shared_ptr<CLogger> mpLogger;
    };
}