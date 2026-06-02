#include "./cOpenGLTexture.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Simpleton {
    COpenGLTexture::~COpenGLTexture() {
        glDeleteTextures(1, &mTextureId);
        delete[] mData;
    }

    void COpenGLTexture::Bind() {
        glBindTexture(GL_TEXTURE_2D, mTextureId);  
    }

    void COpenGLTexture::Unbind() {
        glBindTexture(GL_TEXTURE_2D, 0);  
    }

    bool COpenGLTexture::Init() {
        *mpLogger << "Initializing texture...\n";

        glGenTextures(1, &mTextureId); 
        glBindTexture(GL_TEXTURE_2D, mTextureId);  
        mState = TextureState::Empty;

        *mpLogger << "Initialized texture " << mTextureId << ".\n";
        return true;
    }

    bool COpenGLTexture::LoadData(unsigned char* data, int width, int height, int channelsCount) {
        if(mState == TextureState::Uninited)
            Init();

        *mpLogger << "Loading texture " << mTextureId << " by data...\n";

        mWidth = width;
        mHeight = height;
        mChannelsCount = channelsCount;

        size_t dataSize = width * height * channelsCount;
        mData = new unsigned char[dataSize];
        std::memcpy(mData, data, dataSize);

        int format = GL_RGB;
        if( channelsCount == 4)
            format = GL_RGBA;
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        *mpLogger << "Loaded texture ID: " << mTextureId << ".\n";
        mState = TextureState::Loaded;
        mLoadType = TextureLoadType::Data;
        return true;
    }
}