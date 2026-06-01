#pragma once

#include "simpleton/resources/iTexture.hpp"

namespace Simpleton {
    class COpenGLTexture : public ITexture {
        private:
            unsigned int mTextureId;

        public:
            bool LoadData(int width, int height, int channelsCount, unsigned char* data) override;
    };
}