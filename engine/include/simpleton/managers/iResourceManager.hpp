#pragma once

#include <string>
#include <memory>

#include "simpleton/managers/iManager.hpp"
#include "simpleton/resources/iTexture.hpp"

namespace Simpleton {
    class IResourceManager : private IManager {
        public:
            virtual void AddTexture(std::string textureName, std::shared_ptr<ITexture> texture) = 0;
            virtual std::shared_ptr<ITexture> GetTexture(std::string textureName) = 0;
    };
}