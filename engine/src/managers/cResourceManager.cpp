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
        // Texture* defaultTexture = new Texture(defaultTextureSize, defaultTextureSize, 3, defaultTextureData);
        // defaultTexture->SetFiltering(TextureFiltering::Nearest);
        // AddTexture("default", defaultTexture);

        mIsInitialized = true;
        return mIsInitialized;
    };

    void CResourceManager::OnDestroy() {
        *mpLogger << "Resource Manager destroy...\n";
        mTextures.clear();
    }

    // ITexture CResourceManager::(std::string textureName) {
        
    // }
}