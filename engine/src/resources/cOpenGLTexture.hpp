#pragma once

#include <memory>

#include "simpleton/resources/iTexture.hpp"
#include "../util/cLog.hpp"

namespace Simpleton {
    class COpenGLTexture : public ITexture {
        private:
            unsigned int mTextureId;
            std::shared_ptr<CLogger> mpLogger;

        public:
            ~COpenGLTexture() override
            
            unsigned int GetTextureId() {
                return mTextureId;
            }

            void Bind();
            void Unbind();
            bool Init();
            bool LoadData(unsigned char* data, int width, int height, int channelsCount = 3) override;
    };
}