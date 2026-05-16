#pragma once

#include <string>
#include <filesystem>
namespace fs = std::filesystem;

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Simpleton {
    enum ShaderType {
        VertexShader,
        FragmentShader
    };

    class CShader {
        private:
            unsigned int mVertexShader;
            unsigned int mFragmentShader; 
            unsigned int mShaderProgId;
            bool mIsValid;
            char mErrorLog[512];

        public:
            CShader();
            ~CShader();

            bool CheckProgramValid();

            bool AddShaderSource(ShaderType type, const char* code);
            bool AddShaderFile(ShaderType type, fs::path filePath);

            bool Compile();

            // set uniforms
            void SetUniform(const char* name, float x, float y, float z, float w);
            void SetUniform(const char* name, float x, float y, float z);
            void SetUniform(const char* name, float x, float y);
            void SetUniform(const char* name, int x, int y, int z);
            void SetUniform(const char* name, int i);
            void SetUniform(const char* name, float f);
            void SetUniform(const char* name, glm::mat4 matrix);

            void Bind() const;
            void Unbind() const;

            unsigned int GetProgId() const;

            std::string GetErrorLog();

        private:
            bool CheckShaderValid(ShaderType type);
            void Terminate();

            // Can't always init in constructor before systems are up, manually init check in shader adding functions 
            bool mIsInited = false;
            void Init();
    };
}