#pragma once

#include <glm/glm.hpp>

namespace Simpleton {
    class CMeshVertex {
        public:
            glm::vec3 mPos;
    };

    class CMeshVertexTex : public CMeshVertex {
        public:
            glm::vec2 mTexCoords;
    };
}