#include "./cPrimitiveMesh.hpp"

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

    void CPrimitiveMesh::Draw(const Triangle<float>* pData, unsigned int count) {
        Init();

        glBindVertexArray(mVAO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(pData) * count, pData, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);  
        
        glDrawArrays(GL_TRIANGLES, 0, count);
    }

    void CPrimitiveMesh::Draw(const Point<float>* pData, const unsigned int* pIndices, unsigned int pointsCount, unsigned int indicesCount) {
        Init();

        glBindVertexArray(mVAO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * pointsCount, pData, GL_STATIC_DRAW);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indicesCount, pIndices, GL_STATIC_DRAW);
        
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);  

        glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, 0);
    }
}