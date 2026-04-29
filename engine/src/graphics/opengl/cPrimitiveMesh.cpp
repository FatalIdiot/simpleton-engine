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

        mIsInited = true;
    }

    void CPrimitiveMesh::Draw(const Triangle<float>* pData, unsigned int count) {
        Init();

        glBindVertexArray(mVAO);
        glBindBuffer(GL_ARRAY_BUFFER, mVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(pData) * count, pData, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);  
        
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }
}