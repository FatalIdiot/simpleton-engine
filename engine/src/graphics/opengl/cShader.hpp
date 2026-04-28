#pragma once

#include <string>
#include <filesystem>
namespace fs = std::filesystem;

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
            void SetUniform(const char* name, int i);

            void Bind() const;
            void Unbind() const;

            std::string GetErrorLog();

        private:
            bool CheckShaderValid(ShaderType type);
            void Terminate();

            // Can't always init in constructor before systems are up, manually init check in shader adding functions 
            bool mIsInited = false;
            void Init();
    };
}