#pragma once

namespace Simpleton {
    class ITexture {
        private:
            int mWidth, mHeight, mChannelsCount;
            unsigned char *mData;

        public:
            virtual bool LoadData(int width, int height, int channelsCount, unsigned char* data) = 0;
    };
}