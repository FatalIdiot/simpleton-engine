#include "./cPrimitiveMeshRender.hpp"

#include <iostream>

namespace Simpleton {
    CPrimitiveMeshRender::CPrimitiveMeshRender() {}
    CPrimitiveMeshRender::~CPrimitiveMeshRender() {}

    void CPrimitiveMeshRender::Init() {
        if(mIsInited)
            return;

        glGenVertexArrays(1, &mVAO); 
        glBindVertexArray(mVAO);
        glGenBuffers(1, &mVBO); 
        glBindBuffer(GL_ARRAY_BUFFER, mVBO);
        glGenBuffers(1, &mEBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);

        mIsInited = true;
    }

    void CPrimitiveMeshRender::Draw(const Point<int>* pData, unsigned int pointCount, RenderMode renderMode) {
        glBindVertexArray(mVAO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Point<int>) * pointCount, pData, GL_STATIC_DRAW);
        glVertexAttribIPointer(0, 2, GL_INT, sizeof(Point<int>), (void*)0);
        glEnableVertexAttribArray(0);  
        
        glDrawArrays(renderMode, 0, pointCount);
    }

    void CPrimitiveMeshRender::Draw(const Point<int>* pData, const unsigned int* pIndices, unsigned int pointsCount, 
        unsigned int indicesCount, RenderMode renderMode
    ) {
        glBindVertexArray(mVAO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Point<int>) * pointsCount, pData, GL_STATIC_DRAW);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indicesCount, pIndices, GL_STATIC_DRAW);
        
        glVertexAttribIPointer(0, 2, GL_INT, sizeof(Point<int>), (void*)0);
        glEnableVertexAttribArray(0);  

        glDrawElements(renderMode, indicesCount, GL_UNSIGNED_INT, 0);
    }

    void CPrimitiveMeshRender::Destroy() {
        glBindVertexArray(mVAO);
        glDeleteBuffers(1, &mEBO);
        glDeleteBuffers(1, &mVBO);
        glDeleteVertexArrays(1, &mVAO);
        glBindVertexArray(0);
        mIsInited = false;
    }
}