#include "./cPrimitiveMesh.hpp"

#include <iostream>

namespace Simpleton {
    CPrimitiveMesh::CPrimitiveMesh() {}
    CPrimitiveMesh::~CPrimitiveMesh() {}

    void CPrimitiveMesh::Init() {
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

    void CPrimitiveMesh::Draw(const Point<int>* pData, unsigned int pointCount) {
        Init();

        glBindVertexArray(mVAO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Point<int>) * pointCount, pData, GL_STATIC_DRAW);
        glVertexAttribIPointer(0, 2, GL_INT, sizeof(Point<int>), (void*)0);
        glEnableVertexAttribArray(0);  
        
        glDrawArrays(GL_TRIANGLES, 0, pointCount);
    }

    void CPrimitiveMesh::Draw(const Point<int>* pData, const unsigned int* pIndices, unsigned int pointsCount, unsigned int indicesCount) {
        Init();

        glBindVertexArray(mVAO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Point<int>) * pointsCount, pData, GL_STATIC_DRAW);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indicesCount, pIndices, GL_STATIC_DRAW);
        
        glVertexAttribIPointer(0, 2, GL_INT, sizeof(Point<int>), (void*)0);
        glEnableVertexAttribArray(0);  

        glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, 0);
    }
}