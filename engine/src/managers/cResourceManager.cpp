#include "./cResourceManager.hpp"

namespace Simpleton {
    bool CResourceManager::OnInit(std::shared_ptr<CDependencyResolver> depResolver) {
        mpLogger = depResolver->GetLogger();
        *mpLogger << "Resource Manager init...\n";

         // Create default texture and add to map
        const unsigned int defaultTextureSize = 5, defaultTextureChannels = 3;
        unsigned char defaultTextureData[defaultTextureSize * defaultTextureSize * defaultTextureChannels];
        for(int i = 0; i < defaultTextureSize * defaultTextureSize; i++) {
            if(i % 2 == 0) {
                defaultTextureData[i * 3] = 255;
                defaultTextureData[i * 3 + 1] = 164;
                defaultTextureData[i * 3 + 2] = 210;
            } else {
                defaultTextureData[i * 3] = 0;
                defaultTextureData[i * 3 + 1] = 0;
                defaultTextureData[i * 3 + 2] = 0;
            }
        }
        std::shared_ptr<COpenGLTexture> defaultTexture = std::make_shared<COpenGLTexture>();
        defaultTexture->LoadData(defaultTextureData, defaultTextureSize, defaultTextureSize, defaultTextureChannels);
        AddTexture("default", defaultTexture);

        mIsInitialized = true;
        return mIsInitialized;
    };

    void CResourceManager::OnDestroy() {
        *mpLogger << "Resource Manager destroy...\n";
        mTextures.clear();
    }

    void CResourceManager::AddTexture(std::string textureName, std::shared_ptr<ITexture> texture) {
        mTextures[textureName] = texture;
    }

    std::shared_ptr<ITexture> CResourceManager::GetTexture(std::string textureName) {
        try {
            return mTextures[textureName];
        } catch (const std::out_of_range& e) {
            *mpLogger << "Resource Manager: texture '" << textureName << "' does not exist.\n";
            return mTextures["default"];
        }
    }
}