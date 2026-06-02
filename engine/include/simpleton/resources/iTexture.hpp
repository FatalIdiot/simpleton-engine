#pragma once

namespace Simpleton {
    enum class TextureState {
        Uninited, Empty, Loaded, Corrupted
    };
    enum class TextureLoadType {
        None, Data, File
    };

    class ITexture {
        protected:
            int mWidth, mHeight, mChannelsCount;
            unsigned char *mData;
            TextureState mState = TextureState::Uninited;
            TextureLoadType mLoadType = TextureLoadType::None;

        public:
            virtual ~ITexture() = default;

            int GetWidth() { return mWidth; }
            int GetHeight() { return mHeight; }
            unsigned char* GetData() { return mData; }
            TextureState GetState() { return mState; }
            TextureLoadType GetLoadType() { return mLoadType; }

            virtual bool LoadData(unsigned char* data, int width, int height, int channelsCount = 3) = 0;
    };
}