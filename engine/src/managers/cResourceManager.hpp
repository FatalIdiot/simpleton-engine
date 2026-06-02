#pragma once

#include <map>
#include <string>
#include <memory>

#include "../util/cLog.hpp"
#include "../core/cDependencyResolver.hpp"

#include "./iManagerInternal.hpp"
#include "simpleton/managers/iResourceManager.hpp"

#include "../resources/cOpenGLTexture.hpp"

namespace Simpleton
{
    class CResourceManager : public IResourceManager, public IManagerInternal
    {
        private:
            std::shared_ptr<CLogger> mpLogger;

            std::map<std::string, std::shared_ptr<ITexture>> mTextures;

        public:
            bool OnInit(std::shared_ptr<CDependencyResolver> depResolver);
            void OnDestroy();

            void CResourceManager::AddTexture(std::string textureName, std::shared_ptr<ITexture> texture) override;
            std::shared_ptr<ITexture> CResourceManager::GetTexture(std::string textureName) override;
    };
}